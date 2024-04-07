#ifndef VOLUME_SLIDER
#define VOLUME_SLIDER

#include <QWidget>
#include <QSlider>

class VolumeSlider : public QWidget {
  Q_OBJECT
 public:
  VolumeSlider(QWidget *parent = nullptr);
  void setValue(int value);
  void setMinimum(int value);
  void setMaximum(int value);
 private:
  QSlider *slider;
};

#endif // VOLUME_SLIDER
