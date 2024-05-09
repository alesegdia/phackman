#pragma once

class Constants
{
public:
    static constexpr int WindowWidth = 1920;
    static constexpr int WindowHeight = 1080;
    static constexpr int Scale = 2;

    struct Player
    {
        static constexpr float LowestSpeed = 0.000010f;
        static constexpr float LowSpeed = 0.00003f;
        static constexpr float NormalSpeed = 0.00008f;
        static constexpr float FastSpeed = 0.00012f;
        static constexpr float NormalLowSpeed = 0.00005f;
        static constexpr float Speed = 0.00008f;
    };

    struct GunSkill
    {
        static constexpr float Rate = 0.1e6;
    };

    struct BasicSlime
    {

    };

};
