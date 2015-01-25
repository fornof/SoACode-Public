#include "stdafx.h"
#include "GameSystemFactories.h"

#include <Vorb/ecs/ECS.h>

#include "GameSystem.h"

vcore::EntityID GameSystemFactories::createPlayer(OUT GameSystem* gameSystem, const f64v3& spacePosition,
                                                       const f64q& orientation, float massKg, const f64v3& initialVel,
                                                       float fov, float aspectRatio, float znear, float zfar) {
    vcore::EntityID id = gameSystem->addEntity();

    vcore::ComponentID spCmpId = addSpacePosition(gameSystem, id, spacePosition, orientation);

    vcore::ComponentID pyCmpId = addPhysics(gameSystem, id, massKg, initialVel, spCmpId);

    addAabbCollidable(gameSystem, id, f32v3(1.7f, 3.7f, 1.7f), f32v3(0.0f));

    addFreeMoveInput(gameSystem, id, pyCmpId);

    addFrustumComponent(gameSystem, id, fov, aspectRatio, znear, zfar);

    return id;
}

void GameSystemFactories::destroyPlayer(OUT GameSystem* gameSystem, vcore::EntityID playerEntity) {
    gameSystem->deleteEntity(playerEntity);
}

vcore::ComponentID GameSystemFactories::addFreeMoveInput(OUT GameSystem* gameSystem, vcore::EntityID entity,
                                                                vcore::ComponentID physicsComponent) {
    vcore::ComponentID vmCmpId = gameSystem->addComponent("FreeMove", entity);
    auto& vmCmp = gameSystem->freeMoveInputCT.get(vmCmpId);
    vmCmp.physicsComponent = physicsComponent;
    return vmCmpId;
}

void GameSystemFactories::removeFreeMoveInput(OUT GameSystem* gameSystem, vcore::EntityID entity) {
    gameSystem->deleteComponent("FreeMove", entity);
}

vcore::ComponentID GameSystemFactories::addPhysics(OUT GameSystem* gameSystem, vcore::EntityID entity,
                                                          float massKg, const f64v3& initialVel,
                                                          vcore::ComponentID spacePositionComponent,
                                                          OPT vcore::ComponentID voxelPositionComponent /*= 0*/) {
    vcore::ComponentID pCmpId = gameSystem->addComponent("Physics", entity);
    auto& pCmp = gameSystem->physicsCT.get(pCmpId);
    pCmp.spacePositionComponent = spacePositionComponent;
    pCmp.voxelPositionComponent = voxelPositionComponent;
    pCmp.velocity = initialVel;
    pCmp.mass = massKg;
    return pCmpId;
}

void GameSystemFactories::removePhysics(OUT GameSystem* gameSystem, vcore::EntityID entity) {
    gameSystem->deleteComponent("Physics", entity);
}

vcore::ComponentID GameSystemFactories::addSpacePosition(OUT GameSystem* gameSystem, vcore::EntityID entity,
                                                                const f64v3& position, const f64q& orientation) {
    vcore::ComponentID spCmpId = gameSystem->addComponent("SpacePosition", entity);
    auto& spCmp = gameSystem->spacePositionCT.get(spCmpId);
    spCmp.position = position;
    spCmp.orientation = orientation;
    return spCmpId;
}

void GameSystemFactories::removeSpacePosition(OUT GameSystem* gameSystem, vcore::EntityID entity) {
    gameSystem->deleteComponent("Space Position", entity);
}

vcore::ComponentID GameSystemFactories::addAabbCollidable(OUT GameSystem* gameSystem, vcore::EntityID entity,
                                                                 const f32v3& box, const f32v3& offset) {
    vcore::ComponentID abCmpId = gameSystem->addComponent("AABBCollidable", entity);
    auto& abCmp = gameSystem->aabbCollidableCT.get(abCmpId);
    abCmp.box = f32v3(1.7f, 3.7f, 1.7f);
    abCmp.offset = f32v3(0.0f);
    return abCmpId;
}

void GameSystemFactories::removeAabbCollidable(OUT GameSystem* gameSystem, vcore::EntityID entity) {
    gameSystem->deleteComponent("AABBCollidable", entity);
}

vcore::ComponentID GameSystemFactories::addVoxelPosition(OUT GameSystem* gameSystem, vcore::EntityID entity,
                                                                vcore::ComponentID parentVoxelComponent,
                                                                const VoxelPosition& position, const f64q& orientation,
                                                                vvox::VoxelPlanetMapData mapData) {
    // We need to transition to the voxels
    vcore::ComponentID vpid = gameSystem->addComponent("VoxelPosition", entity);
    auto& vpcmp = gameSystem->voxelPositionCT.get(vpid);
    vpcmp.parentVoxelComponent = parentVoxelComponent;
    vpcmp.position = position;
    vpcmp.orientation = orientation;
    vpcmp.mapData = mapData;
    return vpid;
}

void GameSystemFactories::removeVoxelPosition(OUT GameSystem* gameSystem, vcore::EntityID entity) {
    gameSystem->deleteComponent("VoxelPosition", entity);
}

extern vcore::ComponentID GameSystemFactories::addFrustumComponent(OUT GameSystem* gameSystem, vcore::EntityID entity, float fov, float aspectRatio, float znear, float zfar) {
    vcore::ComponentID fid = gameSystem->addComponent("Frustum", entity);
    auto& fcmp = gameSystem->frustumCT.get(fid);
    fcmp.frustum.setCamInternals(fov, aspectRatio, znear, zfar);
    return fid;
}

extern void GameSystemFactories::removeFrustumComponent(OUT GameSystem* gameSystem, vcore::EntityID entity) {
    gameSystem->deleteComponent("Frustum", entity);
}
