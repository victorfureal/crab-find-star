#ifndef CONSTVAL_H
#define CONSTVAL_H

enum crab_state{exploring = 1,finding = 2,delivering = 3};
enum item_type{crab = 1,star = 2,home = 3};
const int SCENE_WIDTH = 1024;
const int SCENE_HEIGHT = 512;
const int CRAB_SIZE = 64;
const int STAR_NUM = 20;
const int CRAB_HOME_SIZE = 80;
const int CRAB_DETECT_SIZE = 20;
const int STAR_SIZE = 16;

const int ITEM_TYPE = 1;
const int STAR_IS_HOME = 2;

#endif // CONSTVAL_H
