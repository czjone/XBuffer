#ifndef XBUFFER_RUNTIME_HPP
#define XBUFFER_RUNTIME_HPP 1
namespace XBF {
	class XBuffer {
	public:
		explicit XBuffer();
		virtual ~XBuffer();

	public:
		template<typename T>
		static std::shared_ptr<T> Load(const char* data){

		};

		template<typename T>
		inline void ToBytes(T &t) {

		};
	};
}
#endif