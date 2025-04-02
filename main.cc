//==============================================================================================
// Modificado para tener un piso plano, una pared de fondo y una caja en el centro
//==============================================================================================

#include "rtweekend.h"
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"


int main() {
    hittable_list world;

    auto white = make_shared<lambertian>(color(0.6, 0.8, 1.0));
    auto gray  = make_shared<lambertian>(color(0.1, 0.2, 0.4)); 
    auto light = make_shared<diffuse_light>(color(15, 15, 15));


    world.add(make_shared<quad>(
        point3(-1000, 0, -1000), 
        vec3(2000, 0, 0),        
        vec3(0, 0, 2000),        
        gray
    ));

    world.add(make_shared<quad>(
        point3(-1000, 0, 1000), 
        vec3(2000, 0, 0),       
        vec3(0, 1000, 0),       
        white
    ));


    shared_ptr<hittable> box1 = box(
        point3(-82.5, 0, -82.5),  
        point3(82.5, 165, 82.5), 
        gray
    );
    world.add(box1);

    
    world.add(make_shared<quad>(
        point3(-200, 900, -200),
        vec3(400, 0, 0),
        vec3(0, 0, 400),
        light
    ));

    
    hittable_list lights;
    lights.add(make_shared<quad>(
        point3(-200, 900, -200),
        vec3(400, 0, 0),
        vec3(0, 0, 400),
        shared_ptr<material>()  
    ));

    camera cam;
    cam.aspect_ratio      = 1.0;
    cam.image_width       = 600;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 40;
    cam.lookfrom = point3(0, 200, -500);
    cam.lookat   = point3(0, 100, 0);
    cam.vup      = vec3(0, 1, 0);
    cam.defocus_angle = 0;

    cam.render(world, lights);
}
