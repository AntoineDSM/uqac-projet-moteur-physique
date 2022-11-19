#pragma once
#include "GLM/glm/glm.hpp"
#include "GLM/glm/gtc/matrix_transform.hpp"

#include "Camera.h"
#include "Shape.h"
#include "Shader.h"
#include "Cube.h"
#include "Vecteur3D.h"
#include "Rotations/RigidBody.h"

//---------------------------------------------------------------------CLASSE PERMETTANT L'AFFICHAGE DES CONTOURS D'UN "SHAPE"------------------------------------------------------------------------

//Prend en paramètre un rigidbody, qui possède un transform avec position, rotation... récupère les infos de celui-ci et dessine a l'endroit voulue.
class ShapeRenderer
{
public:

    ShapeRenderer(RigidBody* rb) : rb(rb)
    {
        m_shader = new Shader("Shader/cubeShader.vs", "Shader/cubeShader.fs");
        m_shape = new Cube(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 1, 1));//On créer notre forme de cube
    }

    //permet de rendre la forme voulue dans la fenêtre courante.
    void render(GLFWwindow* window, Camera camera)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        glBindVertexArray(m_shape->getVAO());
        m_shader->use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
        m_shader->setMat4("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        m_shader->setMat4("view", view);

        //On recupère position, rotation et taille du rigidbody.
        Vector3D position = rb->transform->getPosition();
        Vector3D rotation = rb->transform->getRotation();
        Vector3D scale = rb->transform->getScale();

        //On applique position et rotation fonction des valeurs récupérées
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
        model = glm::rotate(model, (float)glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
        model = glm::rotate(model, (float)glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, (float)glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
        model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
        m_shader->setMat4("model", model);

        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        m_shader->setVec3("light.position", lightPos);
        m_shader->setVec3("viewPos", camera.Position);

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        m_shader->setVec3("light.ambient", ambientColor);
        m_shader->setVec3("light.diffuse", diffuseColor);
        m_shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        m_shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        m_shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        m_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        m_shader->setFloat("material.shininess", 32.0f);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

private:

    RigidBody* rb;
    Shape* m_shape;
    Shader* m_shader;

};