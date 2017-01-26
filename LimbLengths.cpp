#include "LimbLengths.h"



LimbLengths::LimbLengths(LPCWSTR write_path)
{
	char temp[MAX_PATH];
	sprintf(temp, "%ws", write_path);
	this->write_file = fopen(temp, "wt");
	if(this->write_file == NULL) MessageBox(NULL, (LPCWSTR) "Could not open output file", NULL, MB_OK);
	this->record = false; //We dont record anything at start until clapping is seen
}

void LimbLengths::record_skeleton(Joint * limbs, uint64_t n_joints, HandState lfh, HandState rgh)
{
	
	if (lfh == HandState_Open && rgh == HandState_Open) {
		this->record = true;
	}
	
	if (this->record) {
		uint64_t i;
		for (i = 0; i < n_joints; i++) {
			fprintf(this->write_file, "%f\t%f\t%f\t", limbs[i].Position.X, limbs[i].Position.Y, limbs[i].Position.Z);
		}
		fprintf(this->write_file, "\n");
	}
	
}

float LimbLengths::euclidean_3D(Joint * j1, Joint * j2) {
	float distance = (j1->Position.X - j2->Position.X)*(j1->Position.X - j2->Position.X);
	distance += (j1->Position.Y - j2->Position.Y)*(j1->Position.Y - j2->Position.Y);
	distance += (j1->Position.Z - j2->Position.Z)*(j1->Position.Z - j2->Position.Z);
	return sqrtf(distance);
}

uint64_t LimbLengths::map_table(uint64_t i) {
	
	/*
	JointType_Neck
    JointType_SpineShoulder
    JointType_SpineMid
    JointType_SpineBase
    JointType_ShoulderRight
    JointType_ShoulderLeft
    JointType_HipRight
    JointType_HipLeft
    JointType_ElbowRight
    JointType_WristRight
    JointType_HandRight
    JointType_HandTipRight
    JointType_ThumbRight
    JointType_ElbowLeft
    JointType_WristLeft
    JointType_HandLeft
    JointType_HandTipLeft
    JointType_ThumbLeft
	JointType_KneeRight
    JointType_AnkleRight
    JointType_FootRight
	JointType_KneeLeft
    JointType_AnkleLeft
    JointType_FootLeft
	
	*/
	return 0;
}

LimbLengths::~LimbLengths()
{
	fclose(this->write_file);
}
