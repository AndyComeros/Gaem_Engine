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
    Json::Value objects;

    //skybox
    root["skybox"] = scene->skybox->name;
    
    //lights


    //serialize game objects
    for (auto& it : scene->gameObjects)
    {
        Json::Value jobj = ObjectToJson(it.second);
        objects.append(jobj);
    }
    root["objects"] = objects;

    Json::StreamWriterBuilder builder;
    const std::string json_file = Json::writeString(builder, root);
    out << json_file << std::endl;
    out.close();

}

Scene* SceneLoader::LoadScene(const std::string inName)
{
    Scene* scene = new Scene();

    std::ifstream file(inName);
    Json::Reader reader;
    Json::Value sceneJSON;
    reader.parse(file, sceneJSON);

    ResourceManager& res = ResourceManager::Get();

    scene->skybox = res.GetCubeMap(sceneJSON["skybox"].asString());

    Json::Value objects = sceneJSON["objects"];
    for (int i = 0; i < objects.size(); i++)
    {
        Json::Value jobj = objects[i];

     
        GameObject* go = nullptr;

        if(jobj["type"].asString() == "npc"){
            go = &res.CreateNPCObject(objects[i]["name"].asString(), objects[i]["model"].asString(), objects[i]["shader"].asString());
            for (auto& member : jobj["data"].getMemberNames())
            {
                dynamic_cast<NPC*>(go)->AddData(member, jobj["data"][member].asFloat());
            }
        }
        else if (jobj["type"].asString() == "terrain") {
          
            go = &res.CreateTerrainFromModel(objects[i]["name"].asString(),
                objects[i]["model"].asString(),
                objects[i]["height_texture"].asString(),
                objects[i]["terrain_size"].asInt(),
                objects[i]["texture_scale"].asFloat(),
                objects[i]["scaleX"].asFloat(),
                objects[i]["scaleY"].asFloat(),
                objects[i]["scaleZ"].asFloat());
        }
        else {
            go = &res.CreateGameObject(objects[i]["name"].asString(), objects[i]["model"].asString(), objects[i]["shader"].asString());
        }
        
        
        go->name = jobj["name"].asString();
        go->position.x = jobj["position"][0].asFloat();
        go->position.y = jobj["position"][1].asFloat();
        go->position.z = jobj["position"][2].asFloat();

        go->scale.x = jobj["scale"][0].asFloat();
        go->scale.y = jobj["scale"][1].asFloat();
        go->scale.z = jobj["scale"][2].asFloat();

        go->rotation.x = jobj["rotation"][0].asFloat();
        go->rotation.y = jobj["rotation"][1].asFloat();
        go->rotation.z = jobj["rotation"][2].asFloat();



        scene->AddObject(*go);
    }


    return scene;

}

Json::Value SceneLoader::ObjectToJson(GameObject* obj)
{
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
    if (obj->model_data)
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

    //idendify obj type.
    if (dynamic_cast<NPC*>(obj)) {
        NPC* npc = dynamic_cast<NPC*>(obj);
        jobj["type"] = "npc";
        
        Json::Value data;
        for (auto& it : npc->data) {
            data[it.first] = it.second;
        }
        jobj["data"] = data;
    }
    else if (dynamic_cast<Terrain*>(obj)) {
        Terrain* ter = dynamic_cast<Terrain*>(obj);
        jobj["type"] = "terrain";
        jobj["scaleX"] = ter->scaleX;
        jobj["scaleY"] = ter->scaleY;
        jobj["scaleZ"] = ter->scaleZ;
        jobj["terrain_size"] = ter->GetSize();
        jobj["texture_scale"] = ter->GetSize();

        if(ter->GetHeightTexture())
            jobj["height_texture"] = ter->GetHeightTexture()->name;
    }
    else {
        jobj["type"] = "base";
    }



    return jobj;
}

Json::Value SceneLoader::LightsToJson(Lights* lights)
{
    return Json::Value();
}
