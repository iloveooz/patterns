#include <iostream>
#include <string>
  
// Иерархия классов, определяющая алгоритмы сжатия файлов
class Compression {
public:    
    virtual ~Compression() {}
    virtual void compress(const std::string &file) = 0;
};
  
class ZIP_Compression : public Compression {
public:
    void compress(const std::string &file) {
        std::cout << "ZIP compression for " << file << std::endl;
    }
};
  
class ARJ_Compression : public Compression {
public:
    void compress(const std::string &file) {
        std::cout << "ARJ compression for " << file << std::endl;
    }
};
  
class RAR_Compression : public Compression {
public:
    void compress(const std::string &file) {
        std::cout << "RAR compression for " << file << std::endl;
    }
};

class GZIP_Compresiion : public Compression {
public:
	void compress(const std::string &file) {
		std::cout << "GZIP Compression for " << file << std::endl;
	}
};

// class for using
class Compressor {
public:
	Compressor (Compression *comp) : p(comp) {}
	~Compressor() { delete p; }
	void compress(const std::string &file) const {
		p->compress(file);
	}
private:
	Compression *p;
};

int main() {
	Compressor *p = new Compressor(new GZIP_Compresiion);
	p->compress("file.txt");
	delete p;
	
	system("pause");
	return 0;
}
