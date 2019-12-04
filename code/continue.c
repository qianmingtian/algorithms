
void service_sensing_rcv(struct Mac_packet *pmac_head, ui8_t *pdata, ui32_t data_length)
{
    struct routing *route;
    //目的地址匹配，收下业务数据部分,转交上层
    if (pmac_head->dest == local_variable_information.node_id)
    {
        for (ui32_t i = 0; i < data_length; i++)
        {
            //TODO　：业务数据转交上层
            *(pdata++); //遍历数据部分内容
        }
    }
    else
    {
        //根据目的节点查路由
        route = lookup_routing(pmac_head->dest);

        // 一条可达则转发
        if (route->next_addr == pmac_head->dest)
        {
            pmac_head->st_add = local_variable_information.node_id;
            if (pmac_head->ttl - 1 <= 0)
            {
                free(pmac_head);
                free(pdata);
            }
            else
            {
                pmac_head->ttl = pmac_head->ttl - 1;
                // pmac_head->seq .data= 0;
                pmac->crc.data = 0;
                pmac->crc.data = crc16(pmac, CRC_M_HEAD_NUM, pmac->crc.data); //TODO：mac包里面每个字段都是结构体，如果内存连续，校验不会出问题

                //封装的数据转化数组
                ui8_t sensing_packet[MAXLENGH]; //TODO : 数据包的长度

                ui32_t offset[1] = {0};
                ui32_t char_remainer[1] = {8};
                mac_head_domain_assemble(*pmac_head, sensing_packet, offset, char_remainer);

                offset[0] = offset[0] + 1; //mac头77比特，填充完毕后剩余3位，填写数据从下一个字节开始
                for (i32_t i = 0; i < data_length; i++)
                {
                    sensing_packet[offset[0]] = *pdata;
                    pdata++;
                    offset[0] + = 1;
                }
                //发送数组
                send_data(sensing_packet, mac_head_length + data_length);
            }
        }
        else //不可达，丢弃
        {
            free(pmac_head);
            free(pdata);
        }
    }
}
