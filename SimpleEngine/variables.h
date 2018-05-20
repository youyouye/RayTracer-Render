#ifndef VARIBALES_H_
#define VARIBALES_H_
#include <string>
#include <functional>

typedef unsigned char byte;
extern int width_;
extern int height_;
extern std::string setting_filename_;
extern std::string module_filename_;
extern int sample_;
extern int maxdepth;
extern float eye[3];
extern double camera_param_[9];
extern bool module_type_;
extern std::function<void(std::string)> log_callback_;
extern std::function<void()> end_callback_;

#endif // !VARIBALES_H_
