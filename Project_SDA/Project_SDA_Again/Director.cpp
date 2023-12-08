#include "Director.h"
//Director Parameterized Constructor
Director::Director(Interface2* inter2)
{
	this->inter2 = inter2;
}
//This function will show all the complaints in range
vector<Complaint*> Director::cmps_in_range(tm starttime, tm endtime)
{
	vector<Complaint*> cmps_in_ran = inter2->cmps_in_range(starttime, endtime);
	return cmps_in_ran;

}
//This functions will give details of a specific Complaint
void Director::cmp_details(vector<Complaint*> cmps_in_range, int ind)
{
	inter2->view_cmp_details(cmps_in_range, ind);
}
