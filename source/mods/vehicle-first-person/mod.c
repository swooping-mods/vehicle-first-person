/* M02: activate the game's existing seated first-person camera path. */
#include "base.h"
#include "../../runtime/native/camera.h"
#include "../../runtime/native/input.h"
static PTR seated_f,blend_m;static DRoot active_walker,active_world,active_camera;static PTR active_vehicle;
static unsigned char saved;static int enabled,returning;
static const MoonCameraApiV1 *view_api;static MoonCameraSession view_session;
#include "camera_restore.h"
static int capture_view(void *context){
 PTR walker=context,world=0,camera=0;field_value(walker,seated_f,&saved);field_value(walker,world_f,&world);
 PTR field=get_field(object_class(walker),"viewCamera");if(field)field_value(walker,field,&camera);
 active_walker=dhold(walker);active_world=dhold(world);active_camera=dhold(camera);
 if(!active_walker||!active_world||!active_camera){ddrop(&active_walker);ddrop(&active_world);ddrop(&active_camera);return 0;}return 1;
}
static int before(int id,Context *c){
 (void)id;if(!on_thread())return 0;if(returning){release();if(view_session.token)return 0;}PTR walker=(PTR)c->rcx,world=0,vehicle=0;
 int ready=input_ready(walker,&world,&vehicle,0);int edge=moon_input_action("vehicle-first-person.toggle","Alt+V",ready).pressed;
 PTR camera=0,camera_field=get_field(object_class(walker),"viewCamera");if(camera_field)field_value(walker,camera_field,&camera);
 if(enabled&&(!ready||world!=dget(active_world)||walker!=dget(active_walker)||camera!=dget(active_camera)||vehicle!=active_vehicle))release();
 if(ready&&edge){if(enabled){release();event("third-person-restored");}else{PTR camera=0,field=get_field(object_class(walker),"viewCamera");if(field)field_value(walker,field,&camera);
 if(!moon_camera_begin(&view_session,view_api,"vehicle-first-person",world,walker,camera,MOON_CAMERA_MODE,capture_view,walker)){event("camera-busy");return 0;}enabled=1;active_vehicle=vehicle;unsigned char yes=1;set_field(walker,seated_f,&yes);int ok=1;call(blend_m,walker,0,&ok);if(!ok)release();event(ok?"first-person-enabled":"camera-call-failed");}}
 return 0;
}
int MoonLab_ModStart(PTR domain,PTR game){
 if(!base_bind(domain,game,"vehicle-first-person.jsonl"))return 0;view_api=moon_camera_connect();if(!view_api)return 0;(void)pressed;
 seated_f=get_field(find_class("MoonCleaners","MoonWalker"),"seatedFirstPerson");blend_m=dmethod("MoonCleaners","MoonWalker","StartViewBlend","");
 if(!seated_f||!blend_m||!prepare_hook(method("MoonCleaners","MoonWalker","Update",0),100671733,0,game))return 0;
 before_hook=before;return install_hooks();
}
