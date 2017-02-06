#pragma once
#include <inttypes.h>
#include <Kinect.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

class LimbLengths
{
private:
	Joint * limbs;
	HandState left_h;
	HandState right_h;
	uint64_t n_joints;
	FILE * write_file;
	FILE * write_file_raw;
	clock_t init_time;
	bool record;
	float max_record_time;
public:
	LimbLengths(char * write_path, float time_to_record);
	void LimbLengths::record_skeleton(Joint * limbs, uint64_t n_joints, HandState lfh, HandState rgh);
	~LimbLengths();
private:
	uint64_t LimbLengths::map_table(uint64_t i);
	float euclidean_3D(Joint * j1, Joint * j2);
};

