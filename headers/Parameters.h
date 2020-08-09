#pragma once

//The lower the spawn rate, the more they spawn(Spawn rate must be more than zero)
//spawn rate is half of max health
int cycle = 1000;
int n = 100;
const int initialRabbitNum = 1000;
const int initialWolfNum = 100;

const int rabbitWalk = 35;
const int rabbitMaxHealth = 6;
const int rabbitMaxAge = 10;
const int rabbitSpawnrate = 3;

const int wolfWalk = 50;
const int wolfMaxHealth = 40;
const int wolfMaxAge = 80;
const int wolfSpawnrate = 20;

const int grassWalk = 0;
const int grassMaxHealth = 20;
const int grassMaxAge = 40;
const int grassSpawnrate = 1;