#include <future>
#include <assert.h>

std::promise<int> p;
std::future<int> f(p.get_future());
assert(f.valid());		// 有效

std::shared_future<int> sf(std::move(f));
assert(!f.valid());		// 移动后无效
assert(sf.valid());	


std::shared_future<int> sf(p.get_future());	// 移动构造	


auto sf = p.get_tuture.share();		// 移动构造, 自动推断类型