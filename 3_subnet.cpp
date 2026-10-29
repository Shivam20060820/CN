#include <iostream>
#include <cmath>

int main() {
    int prefix, subnets;
    std::cout << "Enter base prefix (e.g., 24) and number of subnets: ";
    std::cin >> prefix >> subnets;

    // Calculate borrowed bits and new prefix length
    int new_prefix = prefix + std::ceil(std::log2(subnets));
    int total_hosts = 1 << (32 - new_prefix); 
    
    // Shift bits to generate the 32-bit subnet mask
    unsigned int mask = 0xFFFFFFFF << (32 - new_prefix);

    std::cout << "Subnet Mask: " 
              << ((mask >> 24) & 255) << "." 
              << ((mask >> 16) & 255) << "." 
              << ((mask >> 8) & 255) << "." 
              << (mask & 255) << "\n";
    std::cout << "Usable hosts: " << (total_hosts - 2) << "\n";
    
    return 0;
}