#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

//auto state function
#define STATE_define(_statefunc_) void ST_##_statefunc_()
#define STATE(_statefunc_) ST_##_statefunc_


#endif // STATE_H_INCLUDED
