/* Restore the captured targets before releasing the shared camera lease. */
static int restore_view(void *context){
 (void)context;PTR w=dget(active_walker);int ok=1;
 if(moon_camera_target_alive(alive_m,w,&ok)){unsigned char now=0;field_value(w,seated_f,&now);if(now==1)set_field(w,seated_f,&saved);call(blend_m,w,0,&ok);}return ok;
}
static void release(void){returning=1;if(!moon_camera_finish(&view_session,restore_view,0))return;ddrop(&active_walker);ddrop(&active_world);ddrop(&active_camera);active_vehicle=0;enabled=returning=0;}
