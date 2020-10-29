// Copyright saberuster. All Rights Reserved.

#include "GameplayCreationMenu.h"


#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Factories/BlueprintFactory.h"


#define LOCTEXT_NAMESPACE "FUnrealGameplayToolkitEditorModule"

UGameplayCreationMenu::UGameplayCreationMenu()
{
}

struct FUGMenuItem : TSharedFromThis<FUGMenuItem>
{
    TMap<FString, TSharedPtr<FUGMenuItem>> SubItems;

    TSubclassOf<class UObject> CDO;

    FString AssetDefaultName;

    static void BuildMenus_UG(FMenuBuilder& MenuBuilder, TSharedPtr<FUGMenuItem> Item, TArray<FString> SelectedPaths)
    {
        for (auto It : Item->SubItems)
        {
            TSharedPtr<FUGMenuItem> SubItem = It.Value;
            FString CatName = It.Key;
            if (SubItem->SubItems.Num() > 0)
            {
                MenuBuilder.AddSubMenu(
                    FText::FromString(CatName),
                    FText(),
                    FNewMenuDelegate::CreateLambda(
                        [SubItem, SelectedPaths](FMenuBuilder& MenuBuilder)
                        {
                            BuildMenus_UG(MenuBuilder, SubItem, SelectedPaths);
                        }));
            }

            if (SubItem->CDO.Get() != nullptr)
            {
                MenuBuilder.AddMenuEntry(
                    FText::FromString(CatName),
                    FText(),
                    FSlateIcon(),
                    FUIAction(FExecuteAction::CreateLambda([=]()
                    {
                        FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>(
                            "AssetTools");
                        FContentBrowserModule& ContentBrowserModule = FModuleManager::GetModuleChecked<
                            FContentBrowserModule>("ContentBrowser");

                        UBlueprintFactory* BlueprintFactory = NewObject<UBlueprintFactory>();
                        BlueprintFactory->ParentClass = SubItem->CDO;

                        FString PkgName = SelectedPaths[0];
                        FString AssetName = SubItem->AssetDefaultName;

                        AssetToolsModule.Get().CreateUniqueAssetName(PkgName / AssetName, TEXT(""), PkgName, AssetName);
                        ContentBrowserModule.Get().CreateNewAsset(*AssetName, SelectedPaths[0],
                                                                  UBlueprint::StaticClass(), BlueprintFactory);
                    })));
            }
        }
    }
};

void TopMenuBuilderFunc(FMenuBuilder& TopMenuBuilder, TArray<FString> SelectedPaths,
                        TArray<FGameplayCreationData> Definitions)
{
    TopMenuBuilder.AddSubMenu(
        LOCTEXT("FUnrealGameplayToolkitEditorModule", "UnrealGameplayToolkit"),
        LOCTEXT("FUnrealGameplayToolkitEditorModule", "UnrealGameplayToolkit"),
        FNewMenuDelegate::CreateLambda([SelectedPaths, Definitions](FMenuBuilder& SubTopMenuBuilder)
        {
            TSharedPtr<FUGMenuItem> RootMenuItem = MakeShared<FUGMenuItem>();
            for (const FGameplayCreationData& Definition : Definitions)
            {
                if (Definition.ParentGameplayClass == nullptr)
                {
                    continue;
                }
                TArray<FString> CategoryStrings;
                Definition.MenuPath.ParseIntoArray(CategoryStrings, TEXT("|"), true);

                TSharedPtr<FUGMenuItem> CurrentMenuItem = RootMenuItem;
                for (int i = 0; i < CategoryStrings.Num(); ++i)
                {
                    TSharedPtr<FUGMenuItem>& SubMenuItem = CurrentMenuItem->SubItems.FindOrAdd(CategoryStrings[i]);
                    if (!SubMenuItem.IsValid())
                    {
                        SubMenuItem = MakeShared<FUGMenuItem>();
                    }

                    CurrentMenuItem = SubMenuItem;
                }

                CurrentMenuItem->AssetDefaultName = Definition.AssetDefaultName;
                CurrentMenuItem->CDO = Definition.ParentGameplayClass;
            }

            FUGMenuItem::BuildMenus_UG(SubTopMenuBuilder, RootMenuItem, SelectedPaths);
        })
    );
}

void UGameplayCreationMenu::AddMenuExtensions() const
{
    FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(
        TEXT("ContentBrowser"));
    TWeakObjectPtr<const UGameplayCreationMenu> WeakThis(this);
    ContentBrowserModule.GetAllAssetContextMenuExtenders().Add(FContentBrowserMenuExtender_SelectedPaths::CreateLambda(
        [WeakThis](const TArray<FString>& SelectedPaths)
        {
            TSharedRef<FExtender> Extender = MakeShared<FExtender>();
            if (WeakThis.IsValid())
            {
                Extender->AddMenuExtension(
                    "ContentBrowserNewAdvancedAsset",
                    EExtensionHook::After,
                    TSharedPtr<FUICommandList>(),
                    FMenuExtensionDelegate::CreateStatic(&TopMenuBuilderFunc, SelectedPaths, WeakThis->Definitions)
                );
            }

            return Extender;
        }));
}

#undef LOCTEXT_NAMESPACE
