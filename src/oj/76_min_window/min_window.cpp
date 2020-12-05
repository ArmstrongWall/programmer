/**
 * Copyright© 2016-2018. UISEE (SHANGHAI) AUTOMOTIVE TECHNOLOGIES LTD. All rights reserved.
 * LICENSE AGREEMENT
 * The copy of the SOFTWARE is licensed, not sold.
 * Customer owns any media on which the SOFTWARE is recorded, but UISEE and its licensors or
 * suppliers retain ownership of the copy of the SOFTWARE itself, including all copyrights and
 * other intellectual property rights in and to the SOFTWARE (including but not limited to all
 * images, photographs, animations, video, audio, music, text, and other information incorporated
 * into the SOFTWARE), the accompanying printed materials, and any copies of the SOFTWARE.
 * The SOFTWARE is protected by copyright laws and international treaty provisions. Accordingly,
 * Customer is required to treat the SOFTWARE like any other copyrighted material,except as
 * otherwise allowed pursuant to this AGREEMENT and that it may make one copy of the SOFTWARE
 * solely for backup or archive purposes, provided that Customer reproduces all copyright and
 * proprietary notices that are on the original copy. The algorithms, structure, organization
 * and source code of the SOFTWARE are the valuable trade secrets and confidential
 * information of UISEE. Except as otherwise expressly provided herein, neither this AGREEMENT
 * nor UISEE grants Customer any express or implied right under any UISEE patents, copyrights,
 * trademarks, or other intellectual property rights in the SOFTWARE, and all rights, title
 * and interest in and to the SOFTWARE not expressly granted are reserved by UISEE or its
 * licensors or suppliers.
 *
 * @file   min_window.cpp
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-11-30
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-11-30    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <climits>
#include "min_window.h"

/*给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。



示例 1：

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"

示例 2：

输入：s = "a", t = "a"
输出："a"



提示：

1 <= s.length, t.length <= 105
s 和 t 由英文字母组成


进阶：你能设计一个在 o(n) 时间内解决此问题的算法吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-window-substring
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

class Solution {
public:
    std::string minWindow_fail(std::string s, std::string t) {
        std::map<char, std::vector<int>> has_find;
        std::set<char> target;
        for(auto & x : t) {
            target.insert(x);
        }
        std::cout << "target is ";
        for(auto &y : target) {
            std::cout  << y << ",";
        }
        std::cout << "\n";

        for(int i = 0; i < s.size(); i++) {
            if(target.find(s[i]) != target.end()) {
                if(has_find.find(s[i]) == has_find.end()) {
                    has_find[s[i]] = {i};
                } else {
                    has_find[s[i]].push_back(i);
                }
            }
        }
        std::cout << "has_find is \n";
        for(auto &x : has_find) {
            std::cout << "one is ";
            for(auto &y : x.second) {
                std::cout  << y << ",";
            }
            std::cout << "\n";
        }

        if(has_find.size() != target.size()) {
            return {};
        }

        std::set<int> order,res;
        int min = INT_MAX;
        full_order(has_find,order,min, res);
        std::string re;

        for(int i = *(res.begin()); i <= *(--res.end()); i++) {
            re.push_back(s[i]);
        }
        return re;
    }

    void full_order(std::map<char, std::vector<int>> has_find, std::set<int> &order, int &min, std::set<int> &res) {
        if(has_find.empty()) {
            int now_interval = *(--order.end()) - *(order.begin());
            if(min > now_interval) {
                min = now_interval;
                res = order;
            }
            return;
        }

        auto it   = has_find.begin();
        std::map<char, std::vector<int>> has_find_copy = has_find;
        auto it_c = has_find_copy.begin();
        has_find_copy.erase(it_c);
        for(auto &x : (*it).second) {
            order.insert(x);
            full_order(has_find_copy,order,min,res);
            order.erase(x);
        }
    }

    std::string minWindow_time_limit(std::string s, std::string t) {
        std::map<char, std::vector<int>> has_find;
        std::map<char, std::vector<int>> has_find_backup;
        std::map<char, int> target;

        for(int i = 0; i < t.size(); i++) {
            if(target.find(t[i]) == target.end()) {
                target[t[i]] = 1;
            } else {
                target[t[i]]++;
            }
        }

        int head = 0, tail = 0, real_head = 0, real_tail = 0, min_length = INT_MAX;
        std::string res;
        bool find_win = false;
        for(;tail < s.size(); tail++) {
            has_find[s[tail]].push_back(tail);

            while (head <= tail) {
                if(target.find(s[head]) == target.end()) {//在目标值中没有找到
                    head++;
                } else if(has_find[s[head]].size() > target[s[head]]){
                    has_find[s[head]].erase(has_find[s[head]].begin());
                    head++;
                } else {
                    break;
                }
            }

            bool win_ok = is_window_ok(has_find,target);
            if(win_ok) {
                find_win = true;
                int length = tail - head;
                if(min_length > length) {
                    min_length = length;
                    res = s.substr(head,length + 1);
                }
            }
        }

        if(!find_win) {
            return "";
        }
        return res;


    }

    bool is_window_ok(std::map<char, std::vector<int>> has_find, std::map<char, int> target) {
        for(auto &x : target) {
            if(has_find[x.first].size() < x.second) return false;
        }
        return true;
    }

private:
    bool is_window_ok(int map_s[], int map_t[], std::vector<int> &vec_t){
        for (int i = 0; i < vec_t.size(); i++){
            if (map_s[vec_t[i]] < map_t[vec_t[i]]){
                return false;
            }
        }
        return true;
    }
public:
    std::string minWindow(std::string s, std::string t) {
        const int MAX_ARRAY_LEN = 128;
        int map_t[MAX_ARRAY_LEN] = {0};
        int map_s[MAX_ARRAY_LEN] = {0};
        std::vector<int> vec_t;
        for (int i = 0; i < t.length(); i++){
            map_t[t[i]]++;
        }
        for (int i = 0; i < MAX_ARRAY_LEN; i++){
            if (map_t[i] > 0){
                vec_t.push_back(i);
            }
        }

        int window_begin = 0;
        std::string result;
        for (int i = 0; i < s.length(); i++){
            map_s[s[i]]++;
            while(window_begin < i){
                char begin_ch = s[window_begin];
                if (map_t[begin_ch] == 0){
                    window_begin++;
                }
                else if	(map_s[begin_ch] > map_t[begin_ch]){
                    map_s[begin_ch]--;
                    window_begin++;
                }
                else{
                    break;
                }
            }
            if (is_window_ok(map_s, map_t, vec_t)){
                int new_window_len = i - window_begin + 1;
                if (result == "" || result.length() > new_window_len){
                    result = s.substr(window_begin, new_window_len);
                }
            }
        }
        return result;
    }

};

int test_min_window() {

//    std::map<char, std::vector<int>> test_m;
//    test_m['A'] = {3,5};
//    test_m['B'] = {4,6};
//    test_m['C'] = {7,8};
//    std::set<int> order,res;
//    Solution s;
//    int min = INT_MAX;
//    s.full_order(test_m,order,min, res);
//    std::cout << "res is ";
//    for(auto &x : res) {
//        std::cout  << x << ",";
//    }
//    std::cout <<",min is " << min << "\n";

    Solution s;

    std::cout << "min win: "<< s.minWindow("cabwefgewcwaefgcf","cae") << "\n";
    std::cout << "min win: "<< s.minWindow("ab","b") << "\n";
    std::cout << "min win: "<< s.minWindow("cfabccd","ccab") << "\n";
    std::cout << "min win: "<< s.minWindow("aa","aa") << "\n";
    std::cout << "min win: "<< s.minWindow("ADOBECODEBANC","ABC") << "\n";
    std::cout << "min win: "<< s.minWindow("a","aa") << "\n";
    std::cout << "min win: "<< s.minWindow("obzcopzocynyrsgsarijyxnkpnukkrvzuwdjldxndmnvevpgmxrmvfwkutwekrffnloyqnntbdohyfqndhzyoykiripdzwiojyoznbtogjyfpouuxvumtewmmnqnkadvzrvouqfbbdiqremqzgevkbhyoznacqwbhtrcjwfkzpdstpjswnpiqxjhywjanhdwavajrhwtwzlrqwmombxcaijzevbtcfsdcuovckoalcseaesmhrrizcjgxkbartdtotpsefsrjmvksqyahpijsrppdqpvmuocofuunonybjivbjviyftsyiicbzxnwnrmvlgkzticetyfcvqcbjvbufdxgcmesdqnowzpshuwcseenwjqhgsdlxatamysrohfnixfprdsljyyfhrnnjsagtuihuczilgvtfcjwgdhpbixlzmakebszxbhrdibpoxiwztshwczamwnninzmqrmpsviydkptjzpktksrortapgpxwojofxeasoyvyprjoguhqobehugwdvtzlenrcttuitsiijswpogicjolfxhiscjggzzissfcnxnvgftxvbfzkukqrtalvktdjsodmtgzqtuyaqvvrbuexgwqzwduixzrpnvegddyyywaquxjxrnuzlmyipuqotkghfkpknqinoidifnfyczzonxydtqroazxhjnrxfbmtlqcsfhshjrxwqvblovaouxwempdrrplefnxmwrwfjtebrfnfanvvmtbzjesctdgbsfnpxlwihalyiafincfcwgdfkvhebphtxukwgjgplrntsuchyjjuqozakiglangxkttsczhnswjksnuqwflmumpexxrznzwxurrysaokwxxqkrggytvsgkyfjrewrcvntomnoazmzycjrjrqemimyhriyxgrzcfuqtjhvjtuhwfzhwpljzajitrhryaqchnuawbxhxrpvyqcvhpggrpplhychyulijhkglinibedauhvdydkqszdbzfkzbvhldstocgydnbfjkcnkfxcyyfbzmmyojgzmasccaahpdnzproaxnexnkamwmkmwslksfpwirexxtymkmojztgmfhydvlqtddewjvsrmyqjrpycbmndhupmdqqabiuelacuvxnhxgtpvrtwfgzpcrbhhtikbcqpctlxszgpfbgcsbaaiapmtsucocmpecgixshrrnhyrpalralbccnxvjzjllarqhznzghswqsnfuyywmzbopyjyauknxddgdthlabjqtwxpxwljvoxkpjjpfvccyikbbrpdsyvlxscuoofkecwtnfkvcnzbxkeabtdusyhrqklhaqreupakxkfzxgawqfwsaboszvlshwzhosojjotgyagygguzntrouhiweuomqptfjjqsxlbylhwtpssdlltgubczxslqjgxuqnmpynnlwjgmebrpokxjnbiltvbebyytnnjlcwyzignmhedwqbfdepqakrelrdfesqrumptwwgifmmbepiktxavhuavlfaqxqhreznbvvlakzeoomykkzftthoemqwliednfsqcnbexbimrvkdhllcesrlhhjsspvfupxwdybablotibypmjutclgjurbmhztboqatrdwsomnxnmocvixxvfiqwmednahdqhxjkvcyhpxxdmzzuyyqdjibvmfkmonfxmohhshpkhmntnoplphqyprveyfsmsxjfosmicdsjrieeytpnbhlsziwxnpmgoxneqbnufhfwrjbqcsdfarybzwaplmxckkgclvwqdbpumsmqkswmjwnkuqbicykoisqwoootrdpdvcuiuswfqmrkctsgrevcxnyncmivsxbpbxzxpwchiwtkroqisnmrbmefbmatmdknaklpgpyqlsccgunaibsloyqpnsibwuowebomrmcegejozypjzjunjmeygozcjqbnrpakdermjcckartbcppmbtkhkmmtcngteigjnxxyzaibtdcwutkvpwezisskfaeljmxyjwykwglqlnofhycwuivdbnpintuyhtyqpwaoelgpbuwiuyeqhbvkqlsfgmeoheexbhnhutxvnvfjwlzfmvpcghiowocdsjcvqrdmkcizxnivbianfpsnzabxqecinhgfyjrjlbikrrgsbgfgyxtzzwwpayapfgueroncpxogouyrdgzdfucfrywtywjeefkvtzxlwmrniselyeodysirqflpduvibfdvedgcrzpzrunpadvawfsmmddqzaaahfxlifobffbyzqqbtlcpquedzjvykvarayfldvmkapjcfzfbmhscdwhciecsbdledspgpdtsteuafzbrjuvmsfrajtulwirzagiqjdiehefmfifocadxfuxrpsemavncdxuoaetjkavqicgndjkkfhbvbhjdcygfwcwyhpirrfjziqonbyxhibelinpllxsjzoiifscwzlyjdmwhnuovvugfhvquuleuzmehggdfubpzolgbhwyeqekzccuypaspozwuhbzbdqdtejuniuuyagackubauvriwneeqfhtwkocuipcelcfrcjcymcuktegiikyosumeioatfcxrheklookaqekljtvtdwhxsteajevpjviqzudnjnqbucnfvkybggaybebljwcstmktgnipdyrxbgewqczzkaxmeazpzbjsntltjwlmuclxirwytvxgvxscztryubtjweehapvxrguzzsatozzjytnamfyiitreyxmanhzeqwgpoikcjlokebksgkaqetverjegqgkicsyqcktmwjwakivtsxjwrgakphqincqrxqhzbcnxljzwturmsaklhnvyungjrxaonjqomdnxpnvihmwzphkyuhwqwdboabepmwgyatyrgtboiypxfavbjtrgwswyvcqhzwibpisydtmltbkydhznbsvxktyfxopwkxzbftzknnwipghuoijrbgqnzovxckvojvsqqraffwowfvqvfcmiicwitrhxdeombgesxexedlakitfovtydxunqnwqqdeeekiwjnwoshqcsljiicgobbbuqakjdonjawgjlezdnqhfdqnmsuavxdpnfzwipmspiabveaarshzwxmirgkmfncvtdrdvfxkpxlkdokxgtwcskmjryyymcthfnkasinihaunohkxaibtsqelockaefjmsuolebtnepauwmrxutspjwaxbmahsjtkfkxlnszribmeofbkyvbjscjtqjakuwvcgunvnonvqbbggfshauqsyznokqbhowjusypfnecffenojfvlblgzntqzlrgzprvhqnpfrrkzxznieiuivajivzijsqijigtatifmbplzqahuidegfoobpymkputzamzvweiyvvzlwihgmmmrcburbgbsdxrfjsbiylitghgcpqjbevvgypxcybubyoijijrhuzcdijfybqbfowlookqmlnplbxvjjosfqviygqyhgamuwzjklbyzopkrnhbywtfoqomweldmlrhjqswctubiknzzvcztyehouvnyiqnvkufaobehxhrjvtisxjlxoumipzjarwvbsaegdkpbsjmpevjbewzuqnfhoohhmdjgfpmjzdmtmykqvtucptwfidpwtwffzolffzqfdearclkyeecuzabjeqhxpmfodsvisnpxrqowdawheydfyhoexvcmihdlzavtqlshdhdgjzpozvvackebhgqppvcrvymljfvooauxcjnbejdivikcoaugxwzsulgfqdtefpehbrlhaoqxwcancuvbqutnfbuygoemditeagmcveatgaikwflozgdhkyfqmjcruyyuemwbqwxyyfiwnvlmbovlmccaoguieu","cjgamyzjwxrgwedhsexosmswogckohesskteksqgrjonnrwhywxqkqmywqjlxnfrayykqotkzhxmbwvzstrcjfchvluvbaobymlrcgbbqaprwlsqglsrqvynitklvzmvlamqipryqjpmwhdcsxtkutyfoiqljfhxftnnjgmbpdplnuphuksoestuckgopnlwiyltezuwdmhsgzzajtrpnkkswsglhrjprxlvwftbtdtacvclotdcepuahcootzfkwqhtydwrgqrilwvbpadvpzwybmowluikmsfkvbebrxletigjjlealczoqnnejvowptikumnokysfjyoskvsxztnqhcwsamopfzablnrxokdxktrwqjvqfjimneenqvdxufahsshiemfofwlyiionrybfchuucxtyctixlpfrbngiltgtbwivujcyrwutwnuajcxwtfowuuefpnzqljnitpgkobfkqzkzdkwwpksjgzqvoplbzzjuqqgetlojnblslhpatjlzkbuathcuilqzdwfyhwkwxvpicgkxrxweaqevziriwhjzdqanmkljfatjifgaccefukavvsfrbqshhswtchfjkausgaukeapanswimbznstubmswqadckewemzbwdbogogcysfxhzreafwxxwczigwpuvqtathgkpkijqiqrzwugtr") << "\n";

    return 0;
}