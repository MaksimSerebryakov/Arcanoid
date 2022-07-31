#include "arkanoid_impl.h"

#include <GLFW/glfw3.h>

#ifdef USE_ARKANOID_IMPL
Arkanoid* create_arkanoid()
{
    return new ArkanoidImpl();
}
#endif

void ArkanoidImpl::reset(const ArkanoidSettings &settings)
{
    // TODO:
    // remove demo code
    demo_world_size.x = settings.world_size[0];
    demo_world_size.y = settings.world_size[1];
    demo_ball_position = demo_world_size * 0.5f;
    demo_ball_initial_speed = settings.ball_speed;
    demo_ball_radius = settings.ball_radius;
    demo_ball_velocity = Vect(demo_ball_initial_speed);

    // TODO:
    // Implement your game world, bricks and
    // carriage initialization
    
    carriage_position = Vect(demo_world_size.x * 0.5f, demo_world_size.y * 0.9f);
    carriage_height = settings.carriage_height;
    carriage_width = settings.carriage_width;
}

void ArkanoidImpl::update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed)
{
    // TODO:
    // Implement you Arkanoid user input handling
    // and game logic.
    // ...
    
    // TODO:
    // remove demo code
    demo_update(io, debug_data, elapsed);
}

void ArkanoidImpl::draw(ImGuiIO& io, ImDrawList &draw_list)
{
    // TODO:
    // Implement you Arkanoid drawing
    // ...

    // TODO:
    // remove demo code
    demo_draw(io, draw_list);
}

void ArkanoidImpl::demo_update(ImGuiIO& io, ArkanoidDebugData& debug_data, float elapsed)
{
    demo_world_to_screen = Vect(io.DisplaySize.x / demo_world_size.x, io.DisplaySize.y / demo_world_size.y);

    // process user input
    if (io.KeysDown[GLFW_KEY_A])
        demo_ball_velocity.x -= 1.0f;

    if (io.KeysDown[GLFW_KEY_D])
        demo_ball_velocity.x += 1.0f;

    if (io.KeysDown[GLFW_KEY_W])
        demo_ball_velocity.y -= 1.0f;

    if (io.KeysDown[GLFW_KEY_S])
        demo_ball_velocity.y += 1.0f;

    if (io.KeysDown[GLFW_KEY_ESCAPE])
        demo_ball_velocity = Vect(demo_ball_initial_speed);

    // update ball position according
    // its velocity and elapsed time
    demo_ball_position += demo_ball_velocity * elapsed;

    if(demo_ball_position.x < demo_ball_radius)
    {
        demo_ball_position.x += (demo_ball_radius - demo_ball_position.x) * 2.0f;
        demo_ball_velocity.x *= -1.0f;
        
        demo_add_debug_hit(debug_data, Vect(0, demo_ball_position.y), Vect(1, 0));
    }
    else if(demo_ball_position.x > (demo_world_size.x - demo_ball_radius))
    {
        demo_ball_position.x -= (demo_ball_position.x - (demo_world_size.x - demo_ball_radius)) * 2.0f;
        demo_ball_velocity.x *= -1.0f;
        
        demo_add_debug_hit(debug_data, Vect(demo_world_size.x, demo_ball_position.y), Vect(-1, 0));
    }

    if(demo_ball_position.y < demo_ball_radius)
    {
        demo_ball_position.y += (demo_ball_radius - demo_ball_position.y) * 2.0f;
        demo_ball_velocity.y *= -1.0f;

        demo_add_debug_hit(debug_data, Vect(demo_ball_position.x, 0), Vect(0, 1));
    }
    else if(demo_ball_position.y > (demo_world_size.y - demo_ball_radius))
    {
        demo_ball_position.y -= (demo_ball_position.y - (demo_world_size.y - demo_ball_radius)) * 2.0f;
        demo_ball_velocity.y *= -1.0f;

        demo_add_debug_hit(debug_data, Vect(demo_ball_position.x, demo_world_size.y), Vect(0, -1));
    }
}

void ArkanoidImpl::demo_draw(ImGuiIO& io, ImDrawList &draw_list)
{
    Vect ball_screen_pos = demo_ball_position * demo_world_to_screen;
    float ball_screen_radius = demo_ball_radius * demo_world_to_screen.x;
    draw_list.AddCircleFilled(ball_screen_pos, ball_screen_radius, ImColor(100, 255, 100));

    Vect carriage_screen_pos = carriage_position * demo_world_to_screen;
    float carriage_screen_width = carriage_width * demo_world_to_screen.x;
    float carriage_screen_height = carriage_height * demo_world_to_screen.y;
    draw_list.AddRectFilled(
        Vect(
            carriage_screen_pos.x - carriage_screen_width / 2, 
            carriage_screen_pos.y - carriage_screen_height / 2
        ), 
        Vect(
            carriage_screen_pos.x + carriage_screen_width / 2, 
            carriage_screen_pos.y + carriage_screen_height / 2
        ), 
        ImColor(100, 255, 100)
    );
}

void ArkanoidImpl::demo_add_debug_hit(ArkanoidDebugData& debug_data, const Vect& world_pos, const Vect& normal)
{
    ArkanoidDebugData::Hit hit;
    hit.screen_pos = world_pos * demo_world_to_screen;
    hit.normal = normal;
    debug_data.hits.push_back(std::move(hit));
}

