class Geometry {
private:
  static Geometry* instance;
  Geometry() {};

public:
  static Geometry* getInstance();
};
