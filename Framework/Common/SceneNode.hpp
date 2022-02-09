#pragma once
#include <vector>
#include <string>
#include "SceneObject.hpp"

namespace ProjectEngine
{
    class BaseSceneNode
    {
    protected:
        std::string m_strName;
        std::list<std::unique_ptr<BaseSceneNode>> m_Children;
        std::list<std::unique_ptr<SceneObjectTransform>> m_Transforms;

    protected:
        virtual void dump(std::ostream& out) const{}

    public:
        BaseSceneNode() {};
        BaseSceneNode(const char* name) { m_strName = name; };
        BaseSceneNode(const std::string& name) { m_strName = name; };
        BaseSceneNode(const std::string&& name) { m_strName = std::move(name); };
        virtual ~BaseSceneNode() {};

        void AppendChild(std::unique_ptr<BaseSceneNode>&& sub_node)
        {
            m_Children.push_back(std::move(sub_node));
        }

        void AppendChild(std::unique_ptr<SceneObjectTransform>&& transform)
        {
            m_Transforms.push_back(std::move(transform));
        }

        friend std::ostream& operator<<(std::ostream& out, const BaseSceneNode& node)
        {
            static thread_local int32_t indent = 0;
            indent++;

            out << std::string(indent, ' ') << "Scene Node" << std::endl;
            out << std::string(indent, ' ') << "----------" << std::endl;
            out << std::string(indent, ' ') << "Name: " << node.m_strName << std::endl;
            node.dump(out);
            out << std::endl;

            for (const std::unique_ptr<BaseSceneNode>& sub_node : node.m_Children) {
                out << *sub_node << std::endl;
            }

            for (const std::unique_ptr<SceneObjectTransform>& sub_node : node.m_Transforms) {
                out << *sub_node << std::endl;
            }

            indent--;

            return out;
        }
    };

    template <typename T>
    struct SceneNode : public BaseSceneNode {
        std::shared_ptr<T> pSceneObject;
    };

    typedef BaseSceneNode SceneEmptyNode;
    typedef SceneNode<SceneObjectGeometry> SceneGeometryNode;
    typedef SceneNode<SceneObjectLight> SceneLightNode;
    typedef SceneNode<SceneObjectCamera> SceneCameraNode;
}