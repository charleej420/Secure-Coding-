#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
  const auto key_length = key.length();
  const auto source_length = source.length();
  assert(key_length > 0);
  assert(source_length > 0);

  std::string output = source;

  for (size_t i = 0; i < source_length; ++i)
  {
    // XOR each character with the corresponding character from the key
    output[i] = source[i] ^ key[i % key_length];
  }

  assert(output.length() == source_length);
  return output;
}

std::string read_file(const std::string& filename)
{
  std::ifstream file(filename);
  std::stringstream file_stream;
  file_stream << file.rdbuf();
  return file_stream.str();
}
std::string get_student_name(const std::string& string_data)
{
  std::string student_name;

  // Find the first newline
  size_t pos = string_data.find('\n');

  // Did we find a newline?
  if (pos != std::string::npos)
  {
    // We did, so copy that substring as the student name
    student_name = string_data.substr(0, pos);
  }

  return student_name;
}


void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
  std::ofstream file(filename);
  if (file.is_open())
  {
    // Write the student name
    file << student_name << '\n';

    // Get the current timestamp
    time_t now = time(nullptr);
    tm tm_time;
    localtime_s(&tm_time, &now);

    // Write the timestamp in yyyy-mm-dd format
    file << std::put_time(&tm_time, "%Y-%m-%d") << '\n';

    // Write the encryption key
    file << key << '\n';

    // Write the data
    file << data;

    file.close();
  }
}

int main()
{
  std::cout << "Encryption Decryption Test!" << std::endl;

  const std::string file_name = "inputdatafile.txt";
  const std::string encrypted_file_name = "encrypteddatafile.txt";
  const std::string decrypted_file_name = "decrypteddatafile.txt";
  const std::string source_string = read_file(file_name);
  const std::string key = "password";

  const std::string student_name = get_student_name(source_string);

  const std::string encrypted_string = encrypt_decrypt(source_string, key);
  save_data_file(encrypted_file_name, student_name, key, encrypted_string);

  const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);
  save_data_file(decrypted_file_name, student_name, key, decrypted_string);

  std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;

  return 0;
}
