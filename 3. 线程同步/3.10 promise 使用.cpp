#include <future>

template<typename Connection_set, typename T>
void process_connections(Connection_set& q)
{
    while(!done(q))
    {
        for(auto it = q.begin(),end = q.end(); it != end; ++it)
        {
            if(it->has_incoming_data())         // 有数据输入
            {
                data_packet data = it->incoming();

                std::promise<T>& p = it->get_promise(data.id);
                p.set_value(data.val);
            }
            if(it->has_outgoing_data())         // 有数据输出
            {
                outgoing_packet data = it->top_of_outgoing_queue();
                
                it->send(data.val);
                data.promise.set_value(true);
            }
        }
    }
}
