#include "util.h"

/**
 * @brief 外观
 * 分类: 结构型(对象)
 * 为子系统中的一组接口提供一个一致的界面，
 * 外观模式定义了一个高层接口，
 * 这个接口使得子系统更加容易使用。
 * 开放用户真正关心的功能。
*/

// 子系统1
class VideoSystem
{
public:
    string init() const {
        return "视频系统: Ready!\n";
    }
    string play() const {
        return "视频系统: Go!\n";
    }
    string operationX() const {
        return "视频系统: 不常用的操作!\n";
    }
};

class RadioSystem
{
public:
    string init() const {
        return "音频系统: 就绪!\n";
    }
    string play() const {
        return "音频系统: 播放!\n";
    }
    string operationX() const {
        return "音频系统: 不常用的操作!\n";
    }
    string mute() const {
        return "音频系统: 静音!\n";
    }
};

// 外观
class Controller
{
protected:
    VideoSystem* m_video;
    RadioSystem* m_radio;
public:
    Controller(VideoSystem* video = nullptr,
               RadioSystem* radio = nullptr) {
        if (!video) m_video = video;
        else new VideoSystem;

        m_radio = radio ? radio : new RadioSystem;
    }
    ~Controller() {
        delete m_video;
        delete m_radio;
    }

    string start() {
        string str = "控制器启动视频系统:\n";
        str += m_video->init();
        str += m_radio->init();
        str += "控制播放:\n";
        str += m_video->play();
        str += m_radio->play();
        return str;
    }

    string mute() {
        return m_radio->mute();
    }
};

void TestFacade() {
    VideoSystem* video = new VideoSystem;
    RadioSystem* radio = new RadioSystem;
    Controller controller(video, radio);
    cout << controller.start() << endl;
}