package cn.flyaudio.dsp;

interface IdspInterface{
	void onMic_BPF(int start, int end);
	void onMic_EQ(int band, int center, int q, int db);
	void onMic_vol(int db);
	void onAdc0_void(int db);
	void onSpeaker_vol(int db);
	void onLineOut_vol(int db);
	void onHeadSet_voi(int db);
	void showCamera();
}