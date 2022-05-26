#include "Framework/Common/Object/World.h"
#include "Framework/Common/Object/Components/TransformComponent.h"
#include "Framework/Common/Object/Components/MeshRenderComponent.h"
#include <iostream>


int main()
{
    auto world = new ProjectEngine::World();
    auto entity = world->CreateEntity();
    std::cout << entity->GetGuid() << std::endl;

    auto guid = xg::newGuid();
    auto entity2 = world->CreateEntity(guid);
    std::cout << entity2->GetGuid() << std::endl;
    std::cout << guid << std::endl;

    std::cout << "entity count: " << world->GetEntityCount() << std::endl;

    entity2->AddChild(entity);
    std::cout << "children count: " << entity2->GetChildrenCount() << std::endl;
    std::cout << "parent of entity is: " << entity->GetParent()->GetGuid() << std::endl;

    auto comp = entity->GetComponent<ProjectEngine::TransformComponent>();
    comp->SetPosition(Vector3f(1, 1, 1));

    auto comp1 = entity->GetComponent<ProjectEngine::MeshRenderComponent>();

    entity->AddComponent<ProjectEngine::MeshRenderComponent>();
    std::cout << "positoin: " << entity->GetComponent<ProjectEngine::TransformComponent>()->GetPosition() << std::endl;
    entity->RemoveComponent<ProjectEngine::TransformComponent>();

    entity2->RemoveChild(entity);
    std::cout << "RemoveChild " << std::endl;
    std::cout << "children count: " << entity2->GetChildrenCount() << std::endl;

    world->DeleteEntity(guid);
    std::cout << "entity count: " << world->GetEntityCount() << std::endl;

    world->Finalize();
    return 0;

}