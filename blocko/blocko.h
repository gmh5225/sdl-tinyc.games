#pragma once

#ifndef NO_OMPH
        #include <omp.h>
#else
        #define omp_get_num_threads() 0
        #define omp_set_nested(n)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define GL3_PROTOTYPES 1

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#define SDL_DISABLE_IMMINTRIN_H
#include <SDL.h>
#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "../_stb/stb_image.h"

#include "../_osn/open-simplex-noise.c"
struct osn_context *osn_context;
#define noise(x,y,z,scale) open_simplex_noise3(osn_context,(float)(x+0.5)/(scale),(float)(y+0.5)/(scale),(float)(z+0.5)/(scale))

#include "timer.h"
#include "vector.h"

#define STON 34
#define ORE  35
#define OREH 36
#define HARD 37
#define GRAN 38

#define SAND 41
#define DIRT 42
#define WOOD 43

#define GRG1 45
#define GRG2 46
#define GRAS 47

#define BARR 64

#define LASTSOLID (BARR+1) // everything less than here is solid
#define OPEN 75            // empty space
#define WATR 76
#define LITE 77

#define RLEF 81
#define YLEF 82


#define SCALE 3                    // x magnification
#define W 1920                     // window width, height
#define H 1000                     // ^
#define CHUNKW 16                  // chunk size (vao size)
#define CHUNKD 16                  // ^
#define CHUNKW2 (CHUNKW/2)
#define CHUNKD2 (CHUNKD/2)
#define VAOW 64                    // how many VAOs wide
#define VAOD 64                    // how many VAOs deep
#define VAOS (VAOW*VAOD)           // total nr of vbos
#define TILESW (CHUNKW*VAOW)       // total level width, height
#define TILESH 160                 // ^
#define TILESD (CHUNKD*VAOD)       // ^
#define BS (20*SCALE)              // block size
#define BS2 (BS/2)                 // block size in half
#define PLYR_W (14*SCALE)          // physical width and height of the player
#define PLYR_H (36*SCALE)          // ^
#define PLYR_SPD (2*SCALE)         // units per frame
#define PLYR_SPD_R (4*SCALE)       // units per frame
#define PLYR_SPD_S (1*SCALE)       // units per frame
#define EYEDOWN 10                 // how far down are the eyes from the top of the head
#define STARTPX (TILESW*BS2)       // starting position within start screen
#define STARTPY 0                  // ^
#define STARTPZ (TILESD*BS2)       // ^
#define NR_PLAYERS 1
#define JUMP_BUFFER_FRAMES 6
#define GRAV_JUMP 0
#define GRAV_FLOAT 4
#define GRAV_ZERO 14
#define GRAV_MAX 49

#define UP    1
#define EAST  2
#define NORTH 3
#define WEST  4
#define SOUTH 5
#define DOWN  6

#define VERTEX_BUFLEN 100000
#define SUNQLEN 10000
#define GLOQLEN 10000

#define SHADOW_SZ 4096

#define CLAMP(v, l, u) { if (v < l) v = l; else if (v > u) v = u; }
#define ICLAMP(v, l, u) ((v < l) ? l : (v > u) ? u : v)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define true 1
#define false 0

#define PI (3.1415926535)
#define PI2 (PI/2.f)
#define TAU (PI*2.f)

#define PNG0 19

#define DAY_R 1.f
#define DAY_G 1.f
#define DAY_B 1.f
#define NIGHT_R 0.32f
#define NIGHT_G 0.28f
#define NIGHT_B 0.41f
#define DUSK_R 0.8f
#define DUSK_G 0.5f
#define DUSK_B 0.4f
#define FOG_DAY_R 0.3f
#define FOG_DAY_G 0.9f
#define FOG_DAY_B 1.0f
#define FOG_DUSK_R 0.61f
#define FOG_DUSK_G 0.35f
#define FOG_DUSK_B 0.31f
#define FOG_NIGHT_R 0.02f
#define FOG_NIGHT_G 0.01f
#define FOG_NIGHT_B 0.06f

// tile pos-to-mem-location macros
#define T_(x,y,z)    tiles[    ((z - scootz) & (TILESD-1)) * (TILESH+0) * (TILESW+0) + ((x - scootx) & (TILESW-1)) * (TILESH+0) + (y)]
#define SUN_(x,y,z)  sunlight[ ((z - scootz) & (TILESD-1)) * (TILESH+0) * (TILESW+0) + ((x - scootx) & (TILESW-1)) * (TILESH+0) + (y)]
#define GLO_(x,y,z)  glolight[ ((z - scootz) & (TILESD-1)) * (TILESH+0) * (TILESW+0) + ((x - scootx) & (TILESW-1)) * (TILESH+0) + (y)]
#define CORN_(x,y,z) cornlight[((z - scootz) & (TILESD-1)) * (TILESH+1) * (TILESW+1) + ((x - scootx) & (TILESW-1)) * (TILESH+1) + (y)]
#define KORN_(x,y,z) kornlight[((z - scootz) & (TILESD-1)) * (TILESH+1) * (TILESW+1) + ((x - scootx) & (TILESW-1)) * (TILESH+1) + (y)]
#define GNDH_(x,z)   gndheight[((z - scootz) & (TILESD-1))              * (TILESW+0) + ((x - scootx) & (TILESW-1))                   ]

// for terrain/worker
#define TT_(x,y,z)    tiles[    ((z - tscootz) & (TILESD-1)) * (TILESH+0) * (TILESW+0) + ((x - tscootx) & (TILESW-1)) * (TILESH+0) + (y)]
#define TSUN_(x,y,z)  sunlight[ ((z - tscootz) & (TILESD-1)) * (TILESH+0) * (TILESW+0) + ((x - tscootx) & (TILESW-1)) * (TILESH+0) + (y)]
#define TGLO_(x,y,z)  glolight[ ((z - tscootz) & (TILESD-1)) * (TILESH+0) * (TILESW+0) + ((x - tscootx) & (TILESW-1)) * (TILESH+0) + (y)]
#define TCORN_(x,y,z) cornlight[((z - tscootz) & (TILESD-1)) * (TILESH+1) * (TILESW+1) + ((x - tscootx) & (TILESW-1)) * (TILESH+1) + (y)]
#define TKORN_(x,y,z) kornlight[((z - tscootz) & (TILESD-1)) * (TILESH+1) * (TILESW+1) + ((x - tscootx) & (TILESW-1)) * (TILESH+1) + (y)]
#define TGNDH_(x,z)   gndheight[((z - tscootz) & (TILESD-1))              * (TILESW+0) + ((x - tscootx) & (TILESW-1))                   ]

// chunk pos-to-mem-location macros
#define AGEN_(x,z)   already_generated[(z - chunk_scootz) & (VAOD-1)][(x - chunk_scootx) & (VAOW-1)]
#define VAO_(x,z)    vbo[    ((z - chunk_scootz) & (VAOD-1)) * (VAOW) + ((x - chunk_scootx) & (VAOW-1))]
#define VBO_(x,z)    vao[    ((z - chunk_scootz) & (VAOD-1)) * (VAOW) + ((x - chunk_scootx) & (VAOW-1))]
#define VBOLEN_(x,z) vbo_len[((z - chunk_scootz) & (VAOD-1)) * (VAOW) + ((x - chunk_scootx) & (VAOW-1))]

// for terrain/worker
#define TAGEN_(x,z)   already_generated[(z - tchunk_scootz) & (VAOD-1)][(x - tchunk_scootx) & (VAOW-1)]

// helper macros
#define IS_OPAQUE(x,y,z) (T_(x, y, z) < LASTSOLID)
#define IS_SOLID(x,y,z) (T_(x, y, z) < LASTSOLID)
#define ABOVE_GROUND(x,y,z) (GNDH_(x, z) >  y)
#define AT_GROUND(x,y,z)    (GNDH_(x, z) == y)
#define BELOW_GROUND(x,y,z) (GNDH_(x, z) <  y)

#define QITEM(x,y,z) ((struct qitem){x, y, z})
#define DIST_SQ(dx, dy, dz) ((dx)*(dx) + (dy)*(dy) + (dz)*(dz))
#define DIST(dx, dy, dz) (sqrt(DIST_SQ(dx, dy, dz)))

#define B2P(b) ((b)*BS)
#define P2B(p) ((p)/BS)
#define C2B(c) ((c)*CHUNKW)
#define C2P(c) ((c)*BS*CHUNKW)
#define B2C(b) ((b)/CHUNKW)
#define P2C(p) (((p)/CHUNKW)/BS)

// dumb rand -- for simple deterministic rand
unsigned dumb_rand(unsigned *seed) { return (*seed = (1103515245 * *seed + 12345) % 2147483648); }
// helpers for dumb rand, must have local var called seed for all of these
#define RAND (dumb_rand(&seed))
// random float in the range 0-1
#define RAND01 ((double)RAND / 2147483648.0)
// random int in the range lo to hi
#define RANDI(lo,hi) ((RAND % (1 + (hi) - (lo))) + (lo))
// random float in the range lo to hi
#define RANDF(lo,hi) (RAND01 * ((hi) - (lo)) + (lo))
// random true/false, true pct percent of the time
#define RANDP(pct) (RAND01 * 100.0 <= (double)(pct))
// randomly true or false 50/50
#define RANDBOOL (RAND % 2 == 0)
// helpers for deterministically setting seed from several values, plus world_seed
#define SEED1(a)       (world_seed ^ (a << 4))
#define SEED2(a,b)     (world_seed ^ (a << 4) ^ (b << 8))
#define SEED3(a,b,c)   (world_seed ^ (a << 4) ^ (b << 8) ^ (c << 12))
#define SEED4(a,b,c,d) (world_seed ^ (a << 4) ^ (b << 8) ^ (c << 12) ^ (d << 16))

float lerp(float t, float a, float b) { return a + t * (b - a); }

unsigned int vbo[VAOS], vao[VAOS];
size_t vbo_len[VAOS];

struct vbufv { // vertex buffer vertex
        float tex;
        float orient;
        float x, y, z;
        float illum0, illum1, illum2, illum3;
        float glow0, glow1, glow2, glow3;
        float alpha;
};

struct vbufv vbuf[VERTEX_BUFLEN + 1000]; // vertex buffer + padding
struct vbufv *v_limit = vbuf + VERTEX_BUFLEN;
struct vbufv *v = vbuf;

struct vbufv wbuf[VERTEX_BUFLEN + 1000]; // water buffer
struct vbufv *w_limit = wbuf + VERTEX_BUFLEN;
struct vbufv *w = wbuf;

float fog_r, fog_g, fog_b;

unsigned char *tiles;
unsigned char *sunlight;
unsigned char *glolight;
unsigned char gndheight[TILESW * TILESD];
float *cornlight;
float *kornlight;
volatile char already_generated[VAOW][VAOD];

int future_scootx, future_scootz; // pending global map offset
int scootx, scootz;               // actual global map offset
int chunk_scootx, chunk_scootz;   //  ^ in chunks

#define TEST_AREA_SZ 32
int test_area_x = -1;
int test_area_y;
int test_area_z;

struct box { float x, y, z, w, h ,d; };
struct point { float x, y, z; };
struct qchunk { int x, y, z, sqdist; };
struct qitem { int x, y, z; };

struct qitem sunq0_[SUNQLEN+1];
struct qitem sunq1_[SUNQLEN+1];
struct qitem *sunq_curr = sunq0_;
struct qitem *sunq_next = sunq1_;
size_t sq_curr_len;
size_t sq_next_len;

struct qitem gloq0_[GLOQLEN+1];
struct qitem gloq1_[GLOQLEN+1];
struct qitem *gloq_curr = gloq0_;
struct qitem *gloq_next = gloq1_;
size_t gq_curr_len;
size_t gq_next_len;

struct qcave { int x, y, z; int radius_sq; };

struct player {
        struct box pos;
        struct point vel;
        float yaw;
        float pitch;
        int wet;
        int cooldownf;
        int runningf;
        int goingf;
        int goingb;
        int goingl;
        int goingr;
        int jumping;
        int sneaking;
        int running;
        int breaking;
        int building;
        int lighting;
        int cooldown;
        int fvel;
        int rvel;
        int grav;
        int ground;
};

struct player player[NR_PLAYERS] = {{
        .pos.x = STARTPX,
        .pos.y = STARTPY,
        .pos.z = STARTPZ,
        .pos.w = PLYR_W,
        .pos.h = PLYR_H,
        .pos.d = PLYR_W,
        .yaw = 3.1415926535 * 0.5f,
        .grav = GRAV_ZERO,
}};
struct player camplayer;
struct point lerped_pos;
struct point sun_pos;
struct point moon_pos;

SDL_Event event;
SDL_Window *win;

GLuint material_tex_id;
GLuint shadow_tex_id;
GLuint shadow_fbo;

unsigned int prog_id;
unsigned int shadow_prog_id;

//globals
int frame = 0;
int pframe = 0;
unsigned world_seed = 160659;
int noisy = false;
int vsync = false;
int show_fresh_updates = false;
int show_light_values = false;
int show_shadow_map = false;
int help_layer = 1;
int polys = 0;
int shadow_polys = 0;
int sunq_outta_room = 0;
int gloq_outta_room = 0;
int omp_threads = 0;
int lock_culling = false;
int frustum_culling = true;
int zooming = false;
float zoom_amt = 1.f;
float fast = 1.f;
int regulated = true;
int antialiasing = false;
int shadow_mapping = false;
int speedy_sun = false;
int reverse_sun = false;
float sun_pitch = 0.3f; // 0 = east, PI/2 = up, PI = west, 3PI/2 = down
char alert[800]; // only for debugging

int mouselook = true;
int target_x, target_y, target_z;
int place_x, place_y, place_z;
int screenw = W;
int screenh = H;
volatile struct qitem just_generated[VAOW*VAOD];
volatile size_t just_gen_len;

int nr_chunks_generated = 0;
int chunk_gen_ticks = 0;

// glsetup.c protos
int check_program_errors(GLuint shader, char *name);
unsigned int file2shader(unsigned int type, char *filename);

// font.c protos
void font_begin(int w, int h);
void font_add_text(char *s, int inx, int iny, float scale);
void font_end(float r, float g, float b);

// atmosphere.c protos
void sun_draw(float *proj, float *view, float time_of_day, unsigned int texid);

// player.c protos
void lerp_camera(float t, struct player *a, struct player *b);
void update_player(struct player * p, int real);

// collision.c protos
int collide(struct box l, struct box r);
int world_collide(struct box box, int wet);

// test.c protos
int in_test_area(int x, int y, int z);
void build_test_area();
void debrief();

// light.c protos
void sun_enqueue(int x, int y, int z, int base, unsigned char incoming_light);
void glo_enqueue(int x, int y, int z, int base, unsigned char incoming_light);
int step_sunlight();
int step_glolight();
void remove_sunlight(int px, int py, int pz);
void remove_glolight(int px, int py, int pz);

// main.c protos
void recalc_corner_lighting(int xlo, int xhi, int zlo, int zhi);
void set_sunlight(int xlo, int ylo, int zlo, int light);
void set_glolight(int xlo, int ylo, int zlo, int light);
void rayshot(float eye0, float eye1, float eye2, float f0, float f1, float f2);
void move_to_ground(float *inout, int x, int y, int z);
void recalc_gndheight(int x, int z);
void scoot(int x, int z);
void apply_scoot();
