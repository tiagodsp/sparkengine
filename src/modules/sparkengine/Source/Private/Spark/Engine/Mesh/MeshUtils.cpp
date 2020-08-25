#include "sparkengine.PCH.h"
#include "Spark/Engine/Mesh/MeshUtils.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "glm/glm.hpp"

namespace Spark
{
    bool MeshUtils::LoadMeshFromFile(std::vector<MeshSectionData> &MeshSections, std::string Filepath)
    {
        Assimp::Importer assimp;
        const aiScene *scene = assimp.ReadFile(Filepath, aiProcess_Triangulate | aiProcess_PreTransformVertices | aiProcess_MakeLeftHanded);

        if (!scene)
            return false;

        if (scene->HasMeshes())
        {
            MeshSections.empty();
            MeshSections.reserve(scene->mNumMeshes);

            for (uint32 i = 0; i < scene->mNumMeshes; ++i)
            {
                MeshSectionData meshSection;

                for (uint32 m = 0; m < scene->mRootNode->mNumChildren; ++m)
                {
                    aiMatrix4x4 tempTrans = scene->mRootNode->mChildren[m]->mTransformation;
                    glm::mat4 tempMatrix;
                    tempMatrix[0][0] = tempTrans.a1; tempMatrix[1][0] = tempTrans.b1; tempMatrix[2][0] = tempTrans.c1; tempMatrix[3][0] = tempTrans.d1;
                    tempMatrix[0][1] = tempTrans.a2; tempMatrix[1][1] = tempTrans.b2; tempMatrix[2][1] = tempTrans.c2; tempMatrix[3][1] = tempTrans.d2;
                    tempMatrix[0][2] = tempTrans.a3; tempMatrix[1][2] = tempTrans.b3; tempMatrix[2][2] = tempTrans.c3; tempMatrix[3][2] = tempTrans.d3;
                    tempMatrix[0][3] = tempTrans.a4; tempMatrix[1][3] = tempTrans.b4; tempMatrix[2][3] = tempTrans.c4; tempMatrix[3][3] = tempTrans.d4;

                    meshSection.Transform = tempMatrix;
                }

                uint32 numVertices = scene->mMeshes[i]->mNumVertices;
                meshSection.Vertices.reserve(numVertices);
                meshSection.Normals.reserve(numVertices);
                meshSection.Triangles.reserve(numVertices);
                meshSection.UVs.reserve(numVertices);
                meshSection.Colors.reserve(numVertices);
                for (uint32 j = 0; j < scene->mMeshes[i]->mNumVertices; ++j)
                {
                    glm::vec3 vertex = glm::vec3(
                        scene->mMeshes[i]->mVertices[j].x,
                        scene->mMeshes[i]->mVertices[j].z * -1,
                        scene->mMeshes[i]->mVertices[j].y);
                    meshSection.Vertices.push_back(vertex);

                    //Normal
                    if (scene->mMeshes[i]->HasNormals())
                    {
                        glm::vec3 normal = glm::vec3(
                            scene->mMeshes[i]->mNormals[j].x,
                            scene->mMeshes[i]->mNormals[j].z * -1,
                            scene->mMeshes[i]->mNormals[j].y);
                        meshSection.Normals.push_back(normal);
                    }
                    else
                    {
                        meshSection.Normals.push_back(glm::vec3(0));
                    }

                    //UV Coordinates - inconsistent coordinates
                    if (scene->mMeshes[i]->HasTextureCoords(0))
                    {
                        glm::vec2 uv = glm::vec2(scene->mMeshes[i]->mTextureCoords[0][j].x, -scene->mMeshes[i]->mTextureCoords[0][j].y);
                        meshSection.UVs.push_back(uv);
                    }
                    else
                    {
                        meshSection.UVs.push_back(glm::vec2(0));
                    }

                    // //Tangent
                    // if (scene->mMeshes[i]->HasTangentsAndBitangents())
                    // {
                    //     // UE_LOG(LogMeshLoader, Log, TEXT("Has tangent. Working on...\n"));
                    //     glm::vec3 meshTangent = glm::vec3(
                    //         scene->mMeshes[i]->mTangents[j].x,
                    //         scene->mMeshes[i]->mTangents[j].z * -1,
                    //         scene->mMeshes[i]->mTangents[j].y);
                    //     meshSection.Tangents[j] = meshTangent;
                    // }

                    //Vertex color
                    if (scene->mMeshes[i]->HasVertexColors(0))
                    {
                        glm::vec4 color = glm::vec4(
                            scene->mMeshes[i]->mColors[0][j].r,
                            scene->mMeshes[i]->mColors[0][j].g,
                            scene->mMeshes[i]->mColors[0][j].b,
                            scene->mMeshes[i]->mColors[0][j].a);
                        meshSection.Colors.push_back(color);
                    }
                    else
                    {
                        meshSection.Colors.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                    }
                    
                }

                //Triangle number
                for (uint32 l = 0; l < scene->mMeshes[i]->mNumFaces; ++l)
                {
                    for (uint32 m = 0; m < scene->mMeshes[i]->mFaces[l].mNumIndices; ++m)
                    {
                        meshSection.Triangles.push_back(scene->mMeshes[i]->mFaces[l].mIndices[m]);
                    }
                }
                MeshSections.push_back(meshSection);
            }
        }

        return true;
    }
} // namespace Spark
