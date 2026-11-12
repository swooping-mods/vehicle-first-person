static PTR seated_f,blend_m;static DRoot active_walker,active_world,active_camera;static PTR active_vehicle;
static unsigned char saved;static int enabled,returning,view_captured;
static const MoonCameraApiV1 *view_api;static MoonCameraSession view_session;
#include "camera_restore.h"
static int capture_view(void *context){
 PTR walker=context,world=0,camera=0;view_captured=0;field_value(walker,seated_f,&saved);field_value(walker,world_f,&world);
 PTR field=get_field(object_class(walker),"viewCamera");if(field)field_value(walker,field,&camera);
 active_walker=dhold(walker);active_world=dhold(world);active_camera=dhold(camera);
 if(!dget(active_walker)||!dget(active_world)||!dget(active_camera)){ddrop(&active_walker);ddrop(&active_world);ddrop(&active_camera);return 0;}view_captured=1;return 1;
}
#include "view_update.h"
