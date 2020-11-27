#ifndef CONFIGURE_H_
#define CONFIGURE_H_

#include <fcntl.h>

#include <string>
#include <map>

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <InputOutput.pb.h>
#include <Writer.pb.h>

class Configure
{
public:
	inline Configure(const char* input, const char* writer);
	~Configure() = default;

	inline const std::string& get_url() const;
	inline const std::string& get_protocol() const;
	inline std::string get_output_name() const;

private:
	const static std::map<resource::Protocol, std::string> protocol_name;

	template<typename T>
	inline int configure(const char* config_file_name, void* message);

	resource::Urls urls;
	writer::FileName file_properties;
};

Configure::Configure(const char* input, const char* writer)
{
	// TODO: Handle blow errors with throw exeption.
	configure<resource::Urls>(input, static_cast<void*>(&urls));
	configure<writer::FileName>(writer, static_cast<void*>(&file_properties));
}

template<typename T>
int Configure::configure(const char* config_file_name, void* message)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	int file_descriptor = open(config_file_name, O_RDONLY);

	if(file_descriptor < 0)
	{
		std::cerr << " Error opening the file " << std::endl;
		return -1;
	}

	google::protobuf::io::FileInputStream fileInput(file_descriptor);
	fileInput.SetCloseOnDelete( true );

	if (!google::protobuf::TextFormat::Parse(&fileInput,
			static_cast<T*>(message)))
	{
		std::cerr << std::endl << "Failed to parse file!" << std::endl;
		return -1;
	}
	else
		std::cerr << "Read Input File - " << config_file_name << std::endl;

	return 0;
}

const std::string& Configure::get_url() const
{
	return urls.url(0).target_url();
}

const std::string& Configure::get_protocol() const
{
	return protocol_name.at(urls.url(0).protocol());
}

std::string Configure::get_output_name() const
{
	return file_properties.file_name() + "." + file_properties.extention();
}

#endif