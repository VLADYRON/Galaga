//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_WORLD_H
#define GALAGA_WORLD_H


class World
{
    /**
     *  TODO: Put Statemanager here.
     *  Subscribe to onStateChange event.
     *  We will keep a map of state to a vector of pointers to entities in that state.
     *  something like: std::unordered_map<State*, std::vector<Entity*>>
     *
     *  We need to know the active state so that we can easily expose an instantiate method
     *  in this class that will create a new given entity (preferably with a template) for the
     *  active state.
     *
     *  States will query this world object to know about all the entities it contains.
     *  States will also use this object to create/destroy entities.
     *
     *  Q: How will we resolve rendering? it would make sense to implement a virtual update
     *      method on entity class, but since not all entities are drawable, how will we draw from State?
     *
     *          Maybe just have all entities be renderable? probably won't need entities that arent drawable
     *          in this case...
     *
     *          Or we can "side-cast" and if it succeeds, we can pass object to draw method of window
     */
};


#endif //GALAGA_WORLD_H
