#include <vector>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::vector;
struct person{
    static int id_count;
    person();

    int id;
    vector<int> friends;
    bool operator==(const person &p){
        return p.id == this->id;
    }
};

int person::id_count = 0;

person::person(){
    id = id_count;
    id_count++;
    // friends.push_back(id);
}


class group {
public:
    group(int f = 0):relation_flag(f) {}
    void displayGroup();
    bool addMember(person p);
    bool deleteMember(person p);
    bool makeFriend(person p1, person p2);
    bool breakRelation(person p1, person p2);
private:
    int relation_flag;
    vector<person> group_member;
};

void group::displayGroup(){
    for (auto i : group_member){
        cout << "Person_" << i.id 
            << ":" ;
        int flag = 1;
        for (auto j : i.friends){
            flag = 0;
            if (j != i.friends[0])
                cout << ",";
            cout << " " << j;
        }
        if (flag)
            cout << " null";
        cout << endl;
    }
}

bool group::addMember(person  p){
    auto find_result = find(group_member.begin(), group_member.end(), p);
    if (find_result != group_member.end())
        return false;
    if (relation_flag == 1){
        for (auto &i : group_member){
            i.friends.push_back(p.id);
        }
        for (auto i : group_member){
            p.friends.push_back(i.id);
        }
    }
    group_member.push_back(p);
    return true;
}

// TODO: not delete relation 
bool group::deleteMember(person  p){
    auto find_result = find(group_member.begin(), group_member.end(), p);
    if (find_result == group_member.end())
        return false;
    group_member.erase(find_result);
    return true;
}


bool group::makeFriend(person  p1, person p2){
    auto p1_find_result = find(group_member.begin(),group_member.end(),p1);
    auto p2_find_result = find(group_member.begin(),group_member.end(),p2);
    p1_find_result->friends.push_back(p2.id);
    p2_find_result->friends.push_back(p1.id);
    return true;
}

bool group::breakRelation(person p1, person p2){
    auto p1_find_result = find(group_member.begin(),group_member.end(),p1);
    auto p2_find_result = find(group_member.begin(),group_member.end(),p2);

    auto p1_friend_find_result = find(p1_find_result->friends.begin(),p1_find_result->friends.end(),p2.id);
    auto p2_friend_find_result = find(p2_find_result->friends.begin(),p2_find_result->friends.end(),p1.id);
    // if (find_result == p1.friends.end()){
    //     return false;
    // }
    // auto find_result2 = find(p2.friends.begin(), p2.friends.end(),p1.id);
    // if (find_result2 == p2.friends.end()){
    //     return false;
    // }
    p1_find_result->friends.erase(p1_friend_find_result);
    p2_find_result->friends.erase(p2_friend_find_result);

    return true;
}


#include <iostream>
using namespace std;
 void test_1() {
    person mike, jack, lily, carson, sucie;
    group school(0), family_1(1), family_2(1);
    // make group (act as a society)
    school.addMember(mike);
    school.addMember(jack);
    school.addMember(lily);
    family_1.addMember(mike);
    family_1.addMember(carson);
    family_2.addMember(jack);
    family_2.addMember(lily);
    family_2.addMember(sucie);
    // construct relationship in the society
    school.makeFriend(mike, jack);
    school.makeFriend(mike, lily);
    // display the society
    cout << "\n------ SCHOOL -----\n";
    school.displayGroup();
    cout << "\n------ FAMILY_1 -----\n";
    family_1.displayGroup();
    cout << "\n------ FAMILY_2 -----\n";
    family_2.displayGroup();
}
 void test_2() {
    person Baidu, Alibaba, Tencent, NTES, Kingsoft_Antivirus, _360safe;
    group BAT(1), ECommerce(1), Security(1);
    // make group (act as a society)
    BAT.addMember(Baidu);
    BAT.addMember(Alibaba);
    BAT.addMember(Tencent);
    ECommerce.addMember(Baidu);
    ECommerce.addMember(Alibaba);
    ECommerce.addMember(Tencent);
    ECommerce.addMember(NTES);
    Security.addMember(Kingsoft_Antivirus);
    Security.addMember(_360safe);
    // display the society
    cout << "\n------ BAT -----\n";
    BAT.displayGroup();
    cout << "\n------ ECommerce -----\n";
    ECommerce.displayGroup();
    cout << "\n------ Security -----\n";
    Security.displayGroup();
}
 void test_3() {
    person p0, p1, p2, p3, p4;
    group g0(0), g1(0), g2(1);
    // make group (act as a society)
    g0.addMember(p0);
    g0.addMember(p1);
    g0.addMember(p2);
    g1.addMember(p0);
    g1.addMember(p3);
    g2.addMember(p3);
    g2.addMember(p4);
    // construct relationship in the society
    g1.makeFriend(p0, p3);
    g2.breakRelation(p3, p4);
    g0.deleteMember(p2);
    // display the society
    cout << "\n------ G0 -----\n";
    g0.displayGroup();
    cout << "\n------ G1 -----\n";
    g1.displayGroup();
    cout << "\n------ G2 -----\n";
    g2.displayGroup();
}
 void test_4() {
    person p[50];
    group g0(0), g1(1);
    int p_count;
    cin >> p_count;
    // make group (act as a society)
    for (int i = 0; i < p_count/2; i++)
        g0.addMember(p[i]);
    for (int i = p_count/2; i < p_count; i++)
        g1.addMember(p[i]);
    // construct relationship in the society
    for (int i = 0; i < p_count/5; i += 2)
        g0.makeFriend(p[i], p[i+1]);
    for (int i = p_count/2; i < p_count*3/4-1; i += 2)
        g1.breakRelation(p[i], p[i+1]);
    for (int i = p_count/4; i < p_count/2; i++)
        g0.deleteMember(p[i]);
    for (int i = p_count*3/4; i < p_count; i++)
        g1.deleteMember(p[i]);
    // display the society
    cout << "\n------ G0 -----\n";
    g0.displayGroup();
    cout << "\n------ G1 -----\n";
    g1.displayGroup();
}
 int main() {
    int test_id;
    cin >> test_id;
    switch (test_id) {
        case 1:
        test_1();
        break;
        case 2:
        test_2();
        break;
        case 3:
        test_3();
        break;
        case 4:
        test_4();
        break;
        default:
        cout << "wrong input\n";
    }
    return 0;
}
 /* ---------- structure for 'world.h' ----------
 * define the struct and the class functions by yourself #(^_^)#
 * the member function is not complete, add something as you need
 struct person;
 class group {
    void displayGroup();
    bool addMember(person &p);
    bool deleteMember(person &p);
    bool makeFriend(person &p1, person &p2);
    bool breakRelation(person &p1, person &p2);
};
 */
 