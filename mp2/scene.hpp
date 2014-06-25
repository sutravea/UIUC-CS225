#include "image.hpp"
#include <vector>
#include <utility>

using namespace std;

class Scene {
public:
    Scene (int max);
    ~Scene ();
    Scene (const Scene &source);
    const Scene& operator=(const Scene &source);
    void changemaxlayers (int newmax);
    void addpicture (const char *FileName, int index, int x, int y);
    void changelayer (int index, int newindex);
    void translate (int index, int xcoord, int ycoord);
    void deletepicture (int index);
    Image * getpicture (int index) const;
    Image drawscene () const;
private:
    void _clear();
    void _copy(const Scene &source);

    vector<Image*> sceneVector;
    vector<pair<int,int>> coordVector;
    int max;
};
