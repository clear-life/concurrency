#include <map>
#include <mutex>
#include <string>
#include <shared_mutex>

class A
{
	std::map<std::string, std::string> dns;
	mutable std::shared_mutex m;                        // 共享 mutex

public:
	std::string find(std::string& key) const
	{
		std::shared_lock<std::shared_mutex> l(m);       // 共享

		std::map<std::string, std::string>::const_iterator const it = dns.find(key);
		
		return (it == dns.end()) ? std::string() : it->second;
	}

	void update(std::string const& key, std::string const& val)
	{
		std::lock_guard<std::shared_mutex> l(m);        // 排他

		dns[key] = val;
	}
};