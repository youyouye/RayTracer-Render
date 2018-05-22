#include "variables.h"

int width_;
int height_;
std::string setting_filename_;
std::string module_filename_;
int sample_;
int maxdepth;
float eye[3];
double camera_param_[9];
bool module_type_;
std::function<void(const char*, size_t)> log_callback_;
std::function<void()> end_callback_;