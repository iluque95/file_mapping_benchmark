#include <iostream>
#include <memory>
#include <vector>
#include <deque>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>
#include "memmap.hpp"

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
		<< setw(2) << _micros.count() << "μs:";
	os.fill(fill);
	return os;
};


void stream_mapping_vector(std::string &file, const uint32_t iterations)
{
	auto start = std::chrono::high_resolution_clock::now();

	for (auto i=0u; i<iterations; ++i)
	{
		

		std::ifstream ifs(file, std::ios::binary);
		std::vector<char> buffer(std::istreambuf_iterator<char>(ifs), {});
		ifs.close();

	}

	auto stop = std::chrono::high_resolution_clock::now();


	std::cout << "stream_mapping_vector (" << file << ") --> " << iterations << " iteration: ";
	display(std::cout, std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start));
	std::cout << "\n";
}

void stream_mapping_deque(std::string& file, const uint32_t iterations)
{
	auto start = std::chrono::high_resolution_clock::now();

	for (auto i = 0u; i < iterations; ++i)
	{


		std::ifstream ifs(file, std::ios::binary);
		std::deque<char> buffer(std::istreambuf_iterator<char>(ifs), {});
		ifs.close();
	
	}

	auto stop = std::chrono::high_resolution_clock::now();

	std::cout << "stream_mapping_deque (" << file << ") --> " << iterations << " iteration: ";
	display(std::cout, std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start));
	std::cout << "\n";
}

void traditional_read(std::string& file, const uint16_t buffer_size, const uint32_t iterations)
{
	auto start = std::chrono::high_resolution_clock::now();

	for (auto i = 0u; i < iterations; ++i)
	{

		char* buffer = new char[buffer_size];

		std::ifstream ifs(file, std::ios::binary);

		while (ifs.read(buffer, buffer_size)) {}

		ifs.close();

		delete[] buffer;

	}

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "traditional_read (" << file << "). Buffer size: " << buffer_size << " bytes --> " << iterations << " iteration: ";
	display(std::cout, duration);
	std::cout << "\n";
}

void kernel_mapping(std::string& file, const uint32_t iterations)
{
	auto start = std::chrono::high_resolution_clock::now();

	for (auto i = 0u; i < iterations; ++i)
	{

		auto f = map_file(file.c_str());
		unmap_file(f.value());
	
	}

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Kernel mapping (" << file << ") --> " << iterations << " iteration: ";
	display(std::cout, duration);
	std::cout << "\n";
}


int main()
{

	std::string small_file("small.file"), big_file("big.file");

	kernel_mapping(small_file, 1);
	traditional_read(small_file, 512, 1);
	traditional_read(small_file, 1024, 1);
	traditional_read(small_file, 2048, 1);
	traditional_read(small_file, 4096, 1);
	traditional_read(small_file, 8192, 1);
	stream_mapping_deque(small_file, 1);
	stream_mapping_vector(small_file, 1);

	std::cout << "\n";

	kernel_mapping(small_file, 1000);
	traditional_read(small_file, 512, 1000);
	traditional_read(small_file, 1024, 1000);
	traditional_read(small_file, 2048, 1000);
	traditional_read(small_file, 4096, 1000);
	traditional_read(small_file, 8192, 1000);
	stream_mapping_deque(small_file, 1000);
	stream_mapping_vector(small_file, 1000);

	std::cout << "\n";

	kernel_mapping(small_file, 10000);
	traditional_read(small_file, 512, 10000);
	traditional_read(small_file, 1024, 10000);
	traditional_read(small_file, 2048, 10000);
	traditional_read(small_file, 4096, 10000);
	traditional_read(small_file, 8192, 10000);
	stream_mapping_deque(small_file, 10000);
	stream_mapping_vector(small_file, 10000);

	std::cout << "\n\n";

	kernel_mapping(big_file, 1);
	traditional_read(big_file, 512, 1);
	traditional_read(big_file, 1024, 1);
	traditional_read(big_file, 2048, 1);
	traditional_read(big_file, 4096, 1);
	traditional_read(big_file, 8192, 1);
	stream_mapping_deque(big_file, 1);
	stream_mapping_vector(big_file, 1);

	std::cout << "\n";

	kernel_mapping(big_file, 1000);
	traditional_read(big_file, 512, 1000);
	traditional_read(big_file, 1024, 1000);
	traditional_read(big_file, 2048, 1000);
	traditional_read(big_file, 4096, 1000);
	traditional_read(big_file, 8192, 1000);
	stream_mapping_deque(big_file, 1000);
	stream_mapping_vector(big_file, 1000);

	std::cout << "\n";

	kernel_mapping(big_file, 10000);
	traditional_read(big_file, 512, 10000);
	traditional_read(big_file, 1024, 10000);
	traditional_read(big_file, 2048, 10000);
	traditional_read(big_file, 4096, 10000);
	traditional_read(big_file, 8192, 10000);
	stream_mapping_deque(big_file, 10000);
	stream_mapping_vector(big_file, 10000);


	int n;

	std::cin >> n;

}