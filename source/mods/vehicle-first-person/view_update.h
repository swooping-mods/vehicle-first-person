static int before(int id,Context *c){
 (void)id;if(!on_thread())return 0;PTR local=0;
 /* Remote callbacks must not consume input or release the local camera. */
 if(!moon_local_actor_read(&local)||!local){(void)moon_input_action("vehicle-first-person.toggle","Alt+V",0);if(enabled||returning||view_session.token)release();return 0;}
 if(local!=(PTR)c->rcx)return 0;
 if(returning||(view_session.token&&!view_captured)){(void)moon_input_action("vehicle-first-person.toggle","Alt+V",0);release();return 0;}PTR walker=(PTR)c->rcx,world=0,vehicle=0;
 int ready=input_ready(walker,&world,&vehicle,0);int edge=moon_input_action("vehicle-first-person.toggle","Alt+V",ready).pressed;
 PTR camera=0,camera_field=get_field(object_class(walker),"viewCamera");if(camera_field)field_value(walker,camera_field,&camera);
 if(enabled&&(!ready||world!=dget(active_world)||walker!=dget(active_walker)||camera!=dget(active_camera)||vehicle!=active_vehicle)){release();return 0;}
 if(ready&&edge){if(enabled){release();event(view_session.token?"camera-restore-pending":"third-person-restored");}else{PTR camera=0,field=get_field(object_class(walker),"viewCamera");if(field)field_value(walker,field,&camera);
 if(!moon_camera_begin(&view_session,view_api,"vehicle-first-person",world,walker,camera,MOON_CAMERA_MODE,capture_view,walker)){
 /* Failed capture may still own a lease when its release failed. Capture is
  * read-only and drops partial roots; finish can safely retry that bare lease. */
 if(view_session.token){release();event(view_session.token?"camera-restore-pending":"camera-capture-failed");}else event("camera-busy");return 0;}enabled=1;active_vehicle=vehicle;unsigned char yes=1;set_field(walker,seated_f,&yes);int ok=1;call(blend_m,walker,0,&ok);if(!ok)release();event(ok?"first-person-enabled":"camera-call-failed");}}
 return 0;
}
