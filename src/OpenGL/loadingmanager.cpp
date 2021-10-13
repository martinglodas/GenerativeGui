#include <OpenGL/loadingmanager.h>
#include <ResourceManagement/vectortiledatamanager.h>
#include <iostream>

using namespace std;

using std::cout;
using std::endl;

LoadingManager::LoadingManager():
    m_datas(),
    m_mutex()
{
}

LoadingManager::~LoadingManager() {}


void LoadingManager::load(std::shared_ptr<Data> data) {
    data->preload();
    m_mutex.lock();
        m_datas.push_back(data);
    m_mutex.unlock();
}

void LoadingManager::clean_loading_data() {
  m_datas.erase(remove_if(m_datas.begin(), m_datas.end(), [](shared_ptr<Data> const &element){
    return element.use_count() == 1;
  }), m_datas.end());
}

void LoadingManager::update() {
    m_mutex.lock();
    clean_loading_data();
		std::vector<std::shared_ptr<Data>> nextDatas;
		size_t i = 0;
		while(i < m_datas.size()) {
            try {
                auto& data = m_datas.at(i);
                if(data) {
                    if(!data->getLoaded()) {
                        if(data->getPreloaded()) {
                            data->load();
                        } else {
                            nextDatas.push_back(move(data));
                        }
                    }
                }
                i++;
            } catch (exception &e) {
                cout << "Cannot get data at index " << i << endl;
                return;
            }
		}
		m_datas = nextDatas;
    m_mutex.unlock();
}
