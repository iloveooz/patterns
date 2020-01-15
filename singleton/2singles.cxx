
	class Singleton1 {
	private: 
		Singleton1() { }
		Singleton1( const Singleton1& );  
		Singleton1& operator=( Singleton1& );
	public:
		static Singleton1& getInstance() {
			static Singleton1 instance;
			return instance;
		}    
	}; 

	class Singleton2 {
	private:     
		Singleton2( Singleton1& instance): s1( instance) { }
		Singleton2( const Singleton2& );  
		Singleton2& operator = ( Singleton2& );
		Singleton1& s1;
	public:
		static Singleton2& getInstance() {
			static Singleton2 instance( Singleton1::getInstance());
			return instance;
		}    
	}; 

	int main() {
		Singleton2& s = Singleton2::getInstance();  
		return 0;
	}
