/* M02: activate the game's existing seated first-person camera path. */
#include "base.h"
#include "../../runtime/native/camera.h"
#include "../../runtime/native/input.h"
#include "view_runtime.h"
int MoonLab_ModStart(PTR domain,PTR game){
 if(!base_bind(domain,game,"vehicle-first-person.jsonl"))return 0;view_api=moon_camera_connect();if(!view_api)return 0;(void)pressed;
 seated_f=get_field(find_class("MoonCleaners","MoonWalker"),"seatedFirstPerson");blend_m=dmethod("MoonCleaners","MoonWalker","StartViewBlend","");
 if(!seated_f||!blend_m||!prepare_hook(method("MoonCleaners","MoonWalker","Update",0),100671733,0,game))return 0;
 before_hook=before;return install_hooks();
}
