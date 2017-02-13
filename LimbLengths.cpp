#include "LimbLengths.h"



LimbLengths::LimbLengths(char * write_path, float time_to_record, HWND window_owner)
{
	this->window_owner = window_owner;
	this->max_record_time = time_to_record;
	this->write_file = fopen(write_path, "wt");
	strcat(write_path, ".raw.csv");
	this->write_file_raw = fopen(write_path, "wt");
	if(this->write_file == NULL || this->write_file_raw == NULL) MessageBox(NULL, (LPCWSTR) "Could not open output file", NULL, MB_ICONWARNING);
	this->record = false; //We dont record anything at start until clapping is seen
}

void LimbLengths::record_skeleton(Joint * limbs, uint64_t n_joints, HandState lfh, HandState rgh)
{
	
	if (this->record == false && lfh == HandState_Open && rgh == HandState_Open) {
		this->record = true;
		this->init_time = clock();
		fprintf(this->write_file, "tiempo;esq0Inf;esq0X;esq0Y;esq0Z;esq1Inf;esq1X;esq1Y;esq1Z;esq2Inf;esq2X;esq2Y;esq2Z;esq3Inf;esq3X;esq3Y;esq3Z;esq4Inf;esq4X;esq4Y;esq4Z;esq5Inf;esq5X;esq5Y;esq5Z;esq6Inf;esq6X;esq6Y;esq6Z;esq7Inf;esq7X;esq7Y;esq7Z;esq8Inf;esq8X;esq8Y;esq8Z;esq9Inf;esq9X;esq9Y;esq9Z;esq10Inf;esq10X;esq10Y;esq10Z;esq11Inf;esq11X;esq11Y;esq11Z;esq12Inf;esq12X;esq12Y;esq12Z;esq13Inf;esq13X;esq13Y;esq13Z;esq14Inf;esq14X;esq14Y;esq14Z;esq15Inf;esq15X;esq15Y;esq15Z;esq16Inf;esq16X;esq16Y;esq16Z;esq17Inf;esq17X;esq17Y;esq17Z;esq18Inf;esq18X;esq18Y;esq18Z;esq19Inf;esq19X;esq19Y;esq19Z;esq20Inf;esq20X;esq20Y;esq20Z;esq21Inf;esq21X;esq21Y;esq21Z;esq22Inf;esq22X;esq22Y;esq22Z;esq23Inf;esq23X;esq23Y;esq23Z;esq24Inf;esq24X;esq24Y;esq24Z;esqRefInf;esqRefX;esqRefY;esqRefZ\n");
		fprintf(this->write_file_raw, "esq0X;esq0Y;esq0Z;esq1X;esq1Y;esq1Z;esq2X;esq2Y;esq2Z;esq3X;esq3Y;esq3Z;esq4X;esq4Y;esq4Z;esq5X;esq5Y;esq5Z;esq6X;esq6Y;esq6Z;esq7X;esq7Y;esq7Z;esq8X;esq8Y;esq8Z;esq9X;esq9Y;esq9Z;esq10X;esq10Y;esq10Z;esq11X;esq11Y;esq11Z;esq12X;esq12Y;esq12Z;esq13X;esq13Y;esq13Z;esq14X;esq14Y;esq14Z;esq15X;esq15Y;esq15Z;esq16X;esq16Y;esq16Z;esq17X;esq17Y;esq17Z;esq18X;esq18Y;esq18Z;esq19X;esq19Y;esq19Z;esq20X;esq20Y;esq20Z;esq21X;esq21Y;esq21Z;esq22X;esq22Y;esq22Z;esq23X;esq23Y;esq23Z;esq24X;esq24Y;esq24Z;esqRefX;esqRefY;esqRefZ\n");
		
	}
	
	if (this->record) {

		if (this->max_record_time == 0 || this->max_record_time > ((clock() - init_time) / (float)CLOCKS_PER_SEC)) {
			uint64_t i;
			fprintf(this->write_file, "%f;", (clock() - init_time) / (float)CLOCKS_PER_SEC);
			for (i = 0; i < n_joints; i++) {


				if (limbs[i].TrackingState != TrackingState_Inferred) {
					fprintf(this->write_file, "0;%f;%f;%f;", limbs[i].Position.X - limbs[0].Position.X, limbs[i].Position.Y - limbs[0].Position.Y, limbs[i].Position.Z - limbs[0].Position.Z);
				}
				else {
					fprintf(this->write_file, "1;%f;%f;%f;", limbs[i].Position.X - limbs[0].Position.X, limbs[i].Position.Y - limbs[0].Position.Y, limbs[i].Position.Z - limbs[0].Position.Z);
				}

				fprintf(this->write_file_raw, "%f;%f;%f;", limbs[i].Position.X, limbs[i].Position.Y, limbs[i].Position.Z);
			}
			if (limbs[0].TrackingState != TrackingState_Inferred) {
				fprintf(this->write_file, "0;%f;%f;%f\n", limbs[0].Position.X, limbs[0].Position.Y, limbs[0].Position.Z);
			}
			else {
				fprintf(this->write_file, "1;%f;%f;%f\n", limbs[0].Position.X, limbs[0].Position.Y, limbs[0].Position.Z);
			}

			fprintf(this->write_file_raw, "\n");
		}
		
	}

	if (this->max_record_time != 0 && this->max_record_time < ((clock() - init_time) / (float)CLOCKS_PER_SEC)) {
		//Closing time
		SendMessage(this->window_owner, WM_CLOSE, NULL, NULL);
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
	fclose(this->write_file_raw);
}
