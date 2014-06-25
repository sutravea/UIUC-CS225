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
    _clear();
}
void Scene::_clear () {
    for (auto& it : sceneVector) {
        if (it != NULL) {
            delete it;
        }
        it = NULL;
    }
}

Scene::Scene (const Scene& source){
    if (this != &source)
    {
        _clear();
        _copy(source);
     }
}

void Scene:: _copy(const Scene &source){
    max = source.max;
    sceneVector = vector<Image*>(max);
    coordVector = vector<pair<int,int>>(max);

    for(int i = 0; i < max; i++)
    {
        if (source.sceneVector[i] != NULL)
        {
            sceneVector[i] = new Image(*(source.sceneVector[i]));
            coordVector[i] = make_pair(source.coordVector[i].first,source.coordVector[i].second);
        }
    }

}

const Scene& Scene::operator=(const Scene &source){
    if (this != &source){
        _clear();
        _copy(source);
    }
    return *this;
}

void Scene::changemaxlayers (int newmax){
    if (newmax<0)
    {
        cout<<"invalid newmax"<<endl;
        return;
    }

    if(newmax<max)
    {
        for(int i = newmax; i < max; i++)
        {
            if (sceneVector[i] != NULL)
            {
                cout<<"invalid newmax"<<endl;
                return;
            }
        }
        sceneVector.resize(newmax);
        coordVector.resize(newmax);
    }

    else
    {
        sceneVector.resize(newmax, NULL);
        coordVector.resize(newmax);
    }

    max = newmax;

}

void Scene::addpicture (const char *FileName, int index, int x, int y){
    if(index>=max || index < 0)
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
    coordVector[newindex] = coordVector[index];
    sceneVector[index] = NULL;
    coordVector[index] = make_pair(0,0);
}

void Scene::translate (int index, int xcoord, int ycoord){
    if (sceneVector[index] == NULL || index < 0 || index >= max) {
        cout<<"invalid index"<<endl;
        return;
    }

    coordVector[index] = make_pair(xcoord, ycoord);
}

void Scene::deletepicture (int index){
    if(index>=max || index < 0 || sceneVector[index] == NULL)
    {
        cout<<"invalid index"<<endl;
        return;
    }
    
    delete sceneVector[index];
    sceneVector[index] = NULL;
}

Image * Scene::getpicture (int index) const{
    if(index>=max || index < 0)
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
                minw = sceneVector[i]->width() + coordVector[i].first;
            if((sceneVector[i]->height()+coordVector[i].second) > minh)
                minh = sceneVector[i]->height() + coordVector[i].second;
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
