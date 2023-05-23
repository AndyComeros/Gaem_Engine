#include "SceneLoader.h"

SceneLoader::SceneLoader()
{

}

SceneLoader::~SceneLoader()
{

}

void SceneLoader::SaveScene(Scene* scene, const std::string outName)
{
    std::ofstream out(outName);

    Json::Value root;
    Json::Value data;
    Json::Value objects;

    for (auto& it : scene->gameObjects)
    {
        GameObject* obj = it.second;
        Json::Value jobj;

        jobj["name"] = obj->name;
        jobj["position"].append(obj->position.x);
        jobj["position"].append(obj->position.y);
        jobj["position"].append(obj->position.z);
        
        jobj["scale"].append(obj->scale.x);
        jobj["scale"].append(obj->scale.y);
        jobj["scale"].append(obj->scale.z);

        jobj["rotation"].append(obj->rotation.x);
        jobj["rotation"].append(obj->rotation.y);
        jobj["rotation"].append(obj->rotation.z);

        //pointer
        if(obj->model_data)
            jobj["model"] = obj->model_data->name;

        if (obj->shader)
            jobj["shader"] = obj->shader->name;

        //rigidbody
        Json::Value rb;
        rb["mass"] = obj->rigidBody.GetMass();
        rb["mod"] = obj->rigidBody.GetModType();
        rb["damp_linear"] = obj->rigidBody.GetDampeningLinear();
        rb["damp_angle"] = obj->rigidBody.GetDampeningAngle();

        rb["mass_center"].append(obj->rigidBody.GetCenterOfMass().x);
        rb["mass_center"].append(obj->rigidBody.GetCenterOfMass().y);
        rb["mass_center"].append(obj->rigidBody.GetCenterOfMass().z);

        rb["axis_linear_factor"].append(obj->rigidBody.GetAxisLinearFactor().x);
        rb["axis_linear_factor"].append(obj->rigidBody.GetAxisLinearFactor().y);
        rb["axis_linear_factor"].append(obj->rigidBody.GetAxisLinearFactor().z);

        rb["axis_angle_factor"].append(obj->rigidBody.GetAxisAngleFactor().x);
        rb["axis_angle_factor"].append(obj->rigidBody.GetAxisAngleFactor().y);
        rb["axis_angle_factor"].append(obj->rigidBody.GetAxisAngleFactor().z);
        jobj["rigidbody"] = rb;
        //end rigidbody

       
        objects.append(jobj);
    }
    
    root["data"] = data;


    //do once objects are all made
    root["objects"] = objects;

    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, root);
    out << json_file << std::endl;
    out.close();
 




}
