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

Scene::~Scene () {
    for (auto& it : sceneVector) {
        if (it != NULL) {
            delete it;
        }
    }
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
    if(newindex >= max || newindex < 0)
    {
        cout << "invalid index" <<endl;
        return;
    }

    if(index == newindex)
        return;
    
    if(sceneVector[newindex] != NULL)
        delete sceneVector[newindex];

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

Image Scene::drawscene () const{
    unsigned int minw = 0;
    unsigned int minh = 0;
    Image scene = Image();
    for(int i = 0; i < max; i++)
    {
        if (sceneVector[i] != NULL)
        {
            if((sceneVector[i]->width()+coordVector[i].first) > minw)
                minw = sceneVector[i]->width();
            if((sceneVector[i]->height()+coordVector[i].second) > minh)
                minh = sceneVector[i]->height();
        }
    }
    scene.resize(minw, minh);
    
    for(int i = 0; i < max; i++)
    {
        if(sceneVector[i] !=NULL)
        {
            for(unsigned int w = 0; w < sceneVector[i]->width(); w++)
            {
                for(unsigned int h = 0; h < sceneVector[i]->height(); h++)
                {
                    *scene(coordVector[i].first+w,coordVector[i].second+h) = *(*sceneVector[i]) (w,h);
                }
            
            }
        }
    }

    return scene;
}
