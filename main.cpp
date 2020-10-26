#include <iostream>
#include <memory>
#include <vector>
#include <deque>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
#include "memmap.hpp"
#include <filesystem>


std::ostream& display(std::ostream& os, std::chrono::nanoseconds ns)
{
	using namespace std;
	using namespace std::chrono;
	typedef duration<int, ratio<86400>> days;
	char fill = os.fill();
	os.fill('0');

	auto _min = duration_cast<minutes>(ns);
	ns -= _min;
	auto _s = duration_cast<seconds>(ns);
	ns -= _s;
	auto _ms = duration_cast<milliseconds>(ns);
	ns -= _ms;
	auto _ns = duration_cast<nanoseconds>(ns);
	ns -= _ns;
	auto _micros = duration_cast<microseconds>(ns);

	os << setw(2) << _min.count() << "m:"
		<< setw(2) << _s.count() << "s:"
		<< setw(2) << _ms.count() << "ms:"
		<< setw(2) << _ns.count() << "ns:"
		<< setw(2) << _micros.count() << "us:";
	os.fill(fill);
	return os;
};

class tempo
{
public:
	tempo(std::string&& s);
	~tempo();
private:
	decltype(std::chrono::high_resolution_clock::now()) start;
	std::string str;
};

tempo::tempo(std::string&& s) 
{
	str = std::move(s);
	start = std::chrono::high_resolution_clock::now();
}
tempo::~tempo()
{
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << str;
	display(std::cout, std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start));
	std::cout << "\n";
}


void stream_mapping_vector(std::string &file, const uint32_t iterations)
{
	tempo t("stream_mapping_vector (" + file + ") --> " + std::to_string(iterations) + " iteration: ");

	for (auto i=0u; i<iterations; ++i)
	{
		std::ifstream ifs(file, std::ios::binary);
		std::vector<char> buffer(std::istreambuf_iterator<char>(ifs), {});
		ifs.close();

	}
}

void stream_mapping_deque(std::string& file, const uint32_t iterations)
{
	tempo t("stream_mapping_deque (" + file + ") --> " + std::to_string(iterations) + " iteration: ");

	for (auto i = 0u; i < iterations; ++i)
	{
		std::ifstream ifs(file, std::ios::binary);
		std::deque<char> buffer(std::istreambuf_iterator<char>(ifs), {});
		ifs.close();
	
	}
}

void traditional_read(std::string& file, const uint16_t buffer_size, const uint32_t iterations)
{
	tempo t("traditional_read (" + file + "). Buffer size: " + std::to_string(buffer_size) + " bytes --> " + std::to_string(iterations) + " iteration: ");

	for (auto i = 0u; i < iterations; ++i)
	{
		char* buffer = new char[buffer_size];

		std::ifstream ifs(file, std::ios::binary);

		while (ifs.read(buffer, buffer_size)) {}

		ifs.close();

		delete[] buffer;
	}
}

void kernel_mapping(std::string& file, const uint32_t iterations)
{
	tempo t("Kernel mapping (" + file + ") --> " + std::to_string(iterations) + " iteration: ");

	for (auto i = 0u; i < iterations; ++i)
	{
		auto f = map_file(file.c_str());
		unmap_file(f.value());
	}
}

void one_transaction_seek(std::string& file, const uint32_t iterations)
{
	tempo t("one transaction seek (" + file + ") --> " + std::to_string(iterations) + " iteration: ");

	for (auto i = 0u; i < iterations; ++i)
	{
		std::ifstream ifs(file, std::ios::binary);

		auto fsize = ifs.tellg();
		ifs.seekg( 0, std::ios::end );
		fsize = ifs.tellg() - fsize;

		ifs.seekg( 0, std::ios::beg );

		char* buffer = new char[fsize];

		ifs.read(buffer, fsize);

		ifs.close();

		delete[] buffer;
	
	}
}


void one_transaction_fs(std::string& file, const uint32_t iterations)
{
	tempo t("one transaction fs (" + file + ") --> " + std::to_string(iterations) + " iteration: ");

	for (auto i = 0u; i < iterations; ++i)
	{
		std::ifstream ifs(file, std::ios::binary);

		auto fsize = std::filesystem::file_size(file);

		char* buffer = new char[fsize];

		ifs.read(buffer, fsize);

		ifs.close();

		delete[] buffer;
	
	}
}


int main()
{

	std::string small_file("small.file"), big_file("big.file");

	{
		tempo t("Total time taken: ");

		{
			auto it = 1u;

			kernel_mapping(small_file, 1);
			traditional_read(small_file, 512, 1);
			traditional_read(small_file, 1024, 1);
			traditional_read(small_file, 2048, 1);
			traditional_read(small_file, 4096, 1);
			traditional_read(small_file, 8192, 1);
			one_transaction_seek(small_file, 1);
			one_transaction_fs(small_file, 1);
			stream_mapping_deque(small_file, 1);
			stream_mapping_vector(small_file, 1);

			std::cout << "\n";
		}

		{
			auto it = 1000;

			kernel_mapping(small_file, it);
			traditional_read(small_file, 512, it);
			traditional_read(small_file, 1024, it);
			traditional_read(small_file, 2048, it);
			traditional_read(small_file, 4096, it);
			traditional_read(small_file, 8192, it);
			one_transaction_seek(small_file, it);
			one_transaction_fs(small_file, it);
			stream_mapping_deque(small_file, it);
			stream_mapping_vector(small_file, it);

			std::cout << "\n";
		}

		{
			auto it = 10000;

			kernel_mapping(small_file, 10000);
			traditional_read(small_file, 512, 10000);
			traditional_read(small_file, 1024, 10000);
			traditional_read(small_file, 2048, 10000);
			traditional_read(small_file, 4096, 10000);
			traditional_read(small_file, 8192, 10000);
			one_transaction_seek(small_file, 10000);
			one_transaction_fs(small_file, 10000);
			stream_mapping_deque(small_file, 10000);
			stream_mapping_vector(small_file, 10000);

			std::cout << "\n";
		}

		std::cout << "\n";

		{
			auto it = 1;

			kernel_mapping(big_file, it);
			traditional_read(big_file, 512, it);
			traditional_read(big_file, 1024, it);
			traditional_read(big_file, 2048, it);
			traditional_read(big_file, 4096, it);
			traditional_read(big_file, 8192, it);
			one_transaction_seek(big_file, it);
			one_transaction_fs(big_file, it);
			stream_mapping_deque(big_file, it);
			stream_mapping_vector(big_file, it);

			std::cout << "\n";
		}

		{
			auto it = 1000;

			kernel_mapping(big_file, it);
			traditional_read(big_file, 512, it);
			traditional_read(big_file, 1024, it);
			traditional_read(big_file, 2048, it);
			traditional_read(big_file, 4096, it);
			traditional_read(big_file, 8192, it);
			one_transaction_seek(big_file, it);
			one_transaction_fs(big_file, it);
			stream_mapping_deque(big_file, it);
			stream_mapping_vector(big_file, it);

			std::cout << "\n";
		}

		{
			auto it = 10000;

			kernel_mapping(big_file, it);
			traditional_read(big_file, 512, it);
			traditional_read(big_file, 1024, it);
			traditional_read(big_file, 2048, it);
			traditional_read(big_file, 4096, it);
			traditional_read(big_file, 8192, it);
			one_transaction_seek(big_file, it);
			one_transaction_fs(big_file, it);
			stream_mapping_deque(big_file, it);
			stream_mapping_vector(big_file, it);
		}

	}

	std::cin.get();
}