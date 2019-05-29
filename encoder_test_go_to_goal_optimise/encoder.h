//extern float encoder_vals[4];

// constants
extern const float pi;
extern const int L; // Length between robot wheel centres

extern int encoder_start_time_ms; 
extern int encoder_time_ms;
extern int encoder_old_time_ms;  
extern int encoder_time_inc;

extern float dist_left;
extern float dist_right;

extern float dist_left_;
extern float dist_right_;

extern float vel_left;
extern float vel_right;

extern float vel_left_;
extern float vel_right_;


void encoder_update_cog(void);

