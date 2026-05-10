//栈的压入、弹出序列
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pushV int整型vector 
     * @param popV int整型vector 
     * @return bool布尔型
     */
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV)
    {
        stack<int> put,pop;
        int j=0;
for(int i=0;i<pushV.size();i++)
{
    put.push(pushV[i]);
    while(!put.empty()&&j<popV.size()&&put.top()==popV[j])
    {
        put.pop();
        j++;
    }
}
return put.empty();

        // write code here
    }
};