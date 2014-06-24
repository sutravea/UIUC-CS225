#include "scene.hpp"


Scene::Scene (int max){
    sceneVector = vector<Image*>(max);
    for(auto& it : sceneVector)
    {
        it=NULL;
    }
    coordVector = vector<pair<int,int>>(max);
    this->max = max;
}
Scene::~Scene (){
}
Scene::Scene (const Scene &source){}
const Scene& Scene::operator=(const Scene &source){
    return *this;
}
void Scene::changemaxlayers (int newmax){
    if(newmax<max)
    {
        for(int i = newmax; i < max; i++)
        {
            if((sceneVector[i] = NULL))
            {
                cout<<"invalid newmax"<<endl;
            }
        }
    }
    vector<Image*> modifiedSceneVector = vector<Image*>(newmax);
    for(int i = 0; i < max; i++)
    {
        modifiedSceneVector[i] = sceneVector[i];
    }
    for(int i = max; i < newmax; i++)
    {
        modifiedSceneVector[i] = NULL;
    }
}
void Scene::addpicture (const char *FileName, int index, int x, int y){
    if(index>=max)
    {
        cout<<"index out of bounds"<<endl;
    }

    Image* newImage = new Image();
    newImage->readFromFile(FileName);
    sceneVector[index] = newImage;

    coordVector[index] = make_pair(x,y);
}
void Scene::changelayer (int index, int newindex){
    if(index >= max || index < 0)
    {
        cout << "invalid index" <<endl;
        return;
    }
    if(index >= max || index < 0)
    {
        cout << "invalid index" <<endl;
        return;
    }

    if((index = newindex))
        return;
    
    if(sceneVector[newindex] != NULL)
        sceneVector[newindex] = NULL;

    sceneVector[newindex] = sceneVector[index];
    sceneVector[index] = NULL;
}
void Scene::translate (int index, int xcoord, int ycoord){
    if((sceneVector[index] = NULL))
    {
        cout<<"invalid index"<<endl;
        return;
    }
    
    coordVector[index] = make_pair(xcoord, ycoord);
}
void Scene::deletepicture (int index){
    
}
Image * Scene::getpicture (int index) const{
    if(index>=max)
    {
        cout<<"invalid index"<<endl;
        return NULL;
    }

    return sceneVector[index];
}
Image Scene::drawscene () const{return Image();}
