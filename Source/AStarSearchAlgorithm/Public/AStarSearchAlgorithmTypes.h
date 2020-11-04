// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class IAStarCoordinate
{
public:
    virtual ~IAStarCoordinate() = default;
    virtual bool Equals(const IAStarCoordinate& Other) const = 0;

    friend bool operator==(const IAStarCoordinate& Lhs, const IAStarCoordinate& RHS)
    {
        return Lhs.Equals(RHS);
    }

    friend bool operator!=(const IAStarCoordinate& Lhs, const IAStarCoordinate& RHS)
    {
        return !(Lhs == RHS);
    }
};


class FAStarCoordinate2D : public IAStarCoordinate
{
public:

    FAStarCoordinate2D(): X(-1), Y(-1)
    {
    }

    FAStarCoordinate2D(int32 InX, int32 InY): X(InX), Y(InY)
    {
    }

    int32 X;

    int32 Y;

    virtual bool Equals(const IAStarCoordinate& Other) const override
    {
        const FAStarCoordinate2D* StarCoordinate2D = static_cast<const FAStarCoordinate2D*>(&Other);
        if (StarCoordinate2D)
        {
            return X == StarCoordinate2D->X && Y == StarCoordinate2D->Y;
        }
        return false;
    }
};
