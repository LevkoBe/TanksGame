#pragma once

enum ProjectileType {
    CannonBall, // basic
    FireBall,   // burns
    SnowBall,   // slows down
    Chip,       // turns into an ally
    Magnet,     // attracts to itself
    LazerBeam,  // basically basic
    Reducer,    // makes smaller
    BombaBall,  // reflects from walls till collision with a tank
    BlackHole,  // absorbs everything
    SelfGuided, // maze-solving, bots-killing
};