/****************************************************************
 *								*
 *	Copyright 2010, 2012 Fidelity Information Services, Inc	*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

/* Generated by /tmp/fisgtm/sr_linux/gen_gtm_threadgbl_deftypes.csh */

#ifndef GTM_THREADGBL_DEFTYPES_INCLUDED
#define GTM_THREADGBL_DEFTYPES_INCLUDED
/* Output selection criteria for PRO build */
#if !defined(DEBUG) || defined(PRO_BUILD)
# define ggo_grabbing_crit 0
# define ggt_grabbing_crit gd_region *
# define ggo_boolchain 8
# define ggt_boolchain triple
# define ggo_boolchain_ptr 144
# define ggt_boolchain_ptr triple *
# define ggo_code_generated 152
# define ggt_code_generated boolean_t
# define ggo_codegen_padlen 156
# define ggt_codegen_padlen int4
# define ggo_compile_time 160
# define ggt_compile_time boolean_t
# define ggo_curtchain 168
# define ggt_curtchain triple *
# define ggo_director_ident 176
# define ggt_director_ident mstr
# define ggo_director_mval 192
# define ggt_director_mval mval
# define ggo_director_token 224
# define ggt_director_token char
# define ggo_dollar_zcstatus 228
# define ggt_dollar_zcstatus int4
# define ggo_expr_depth 232
# define ggt_expr_depth unsigned int
# define ggo_expr_start 240
# define ggt_expr_start triple *
# define ggo_expr_start_orig 248
# define ggt_expr_start_orig triple *
# define ggo_for_nest_level 256
# define ggt_for_nest_level uint4
# define ggo_for_stack_ptr 264
# define ggt_for_stack_ptr oprtype **
# define ggo_gtm_fullbool 272
# define ggt_gtm_fullbool unsigned int
# define ggo_ind_result_array 280
# define ggt_ind_result_array mval **
# define ggo_ind_result_sp 288
# define ggt_ind_result_sp mval **
# define ggo_ind_result_top 296
# define ggt_ind_result_top mval **
# define ggo_ind_source_array 304
# define ggt_ind_source_array mval **
# define ggo_ind_source_sp 312
# define ggt_ind_source_sp mval **
# define ggo_ind_source_top 320
# define ggt_ind_source_top mval **
# define ggo_last_source_column 328
# define ggt_last_source_column short int
# define ggo_pos_in_chain 336
# define ggt_pos_in_chain triple
# define ggo_s2n_intlit 472
# define ggt_s2n_intlit boolean_t
# define ggo_saw_side_effect 476
# define ggt_saw_side_effect boolean_t
# define ggo_shift_side_effects 480
# define ggt_shift_side_effects int
# define ggo_source_error_found 484
# define ggt_source_error_found int4
# define ggo_temp_subs 488
# define ggt_temp_subs boolean_t
# define ggo_trigger_compile 492
# define ggt_trigger_compile boolean_t
# define ggo_window_ident 496
# define ggt_window_ident mstr
# define ggo_window_mval 512
# define ggt_window_mval mval
# define ggo_window_token 544
# define ggt_window_token char
# define ggo_dbinit_max_hrtbt_delta 548
# define ggt_dbinit_max_hrtbt_delta uint4
# define ggo_donot_commit 552
# define ggt_donot_commit boolean_t
# define ggo_donot_write_inctn_in_wcs_recover 556
# define ggt_donot_write_inctn_in_wcs_recover boolean_t
# define ggo_gd_targ_addr 560
# define ggt_gd_targ_addr gd_addr *
# define ggo_gtm_gvundef_fatal 568
# define ggt_gtm_gvundef_fatal boolean_t
# define ggo_gv_extname_size 572
# define ggt_gv_extname_size int4
# define ggo_gv_last_subsc_null 576
# define ggt_gv_last_subsc_null boolean_t
# define ggo_gv_mergekey2 584
# define ggt_gv_mergekey2 gv_key *
# define ggo_gv_reorgkey 592
# define ggt_gv_reorgkey gv_key *
# define ggo_gv_some_subsc_null 600
# define ggt_gv_some_subsc_null boolean_t
# define ggo_gv_sparekey 608
# define ggt_gv_sparekey gv_key *
# define ggo_gv_sparekey_mval 616
# define ggt_gv_sparekey_mval mval
# define ggo_gv_sparekey_size 648
# define ggt_gv_sparekey_size int4
# define ggo_gv_tporigkey_ptr 656
# define ggt_gv_tporigkey_ptr gv_orig_key_array *
# define ggo_in_gvcst_redo_root_search 664
# define ggt_in_gvcst_redo_root_search boolean_t
# define ggo_in_op_gvget 668
# define ggt_in_op_gvget boolean_t
# define ggo_issue_DBROLLEDBACK_anyways 672
# define ggt_issue_DBROLLEDBACK_anyways boolean_t
# define ggo_last_fnquery_return_subcnt 676
# define ggt_last_fnquery_return_subcnt int
# define ggo_last_fnquery_return_varname 680
# define ggt_last_fnquery_return_varname mval
# define ggo_new_dbinit_ipc 712
# define ggt_new_dbinit_ipc int4
# define ggo_ok_to_call_wcs_recover 716
# define ggt_ok_to_call_wcs_recover boolean_t
# define ggo_only_reset_clues_if_onln_rlbk 720
# define ggt_only_reset_clues_if_onln_rlbk boolean_t
# define ggo_prev_gv_target 728
# define ggt_prev_gv_target gv_namehead *
# define ggo_ready2signal_gvundef 736
# define ggt_ready2signal_gvundef boolean_t
# define ggo_semwait2long 740
# define ggt_semwait2long volatile boolean_t
# define ggo_tp_restart_count 744
# define ggt_tp_restart_count uint4
# define ggo_tp_restart_dont_counts 748
# define ggt_tp_restart_dont_counts uint4
# define ggo_tp_restart_entryref 752
# define ggt_tp_restart_entryref mval
# define ggo_tp_restart_failhist_indx 784
# define ggt_tp_restart_failhist_indx int4
# define ggo_tp_restart_needlock_cnt 788
# define ggt_tp_restart_needlock_cnt uint4
# define ggo_tp_restart_needlock_tn 792
# define ggt_tp_restart_needlock_tn trans_num
# define ggo_tprestart_syslog_delta 800
# define ggt_tprestart_syslog_delta int4
# define ggo_tprestart_syslog_limit 804
# define ggt_tprestart_syslog_limit int4
# define ggo_transform 808
# define ggt_transform boolean_t
# define ggo_wcs_recover_done 812
# define ggt_wcs_recover_done boolean_t
# define ggo_in_op_fnnext 816
# define ggt_in_op_fnnext boolean_t
# define ggo_local_collseq 824
# define ggt_local_collseq collseq *
# define ggo_local_collseq_stdnull 832
# define ggt_local_collseq_stdnull boolean_t
# define ggo_lv_null_subs 836
# define ggt_lv_null_subs int
# define ggo_max_lcl_coll_xform_bufsiz 840
# define ggt_max_lcl_coll_xform_bufsiz int
# define ggo_replgbl 848
# define ggt_replgbl replgbl_t
# define ggo_collseq_list 872
# define ggt_collseq_list collseq *
# define ggo_create_fatal_error_zshow_dmp_fptr 880
# define ggt_create_fatal_error_zshow_dmp_fptr void
# define gga_create_fatal_error_zshow_dmp_fptr (void)
typedef void (*ggf_create_fatal_error_zshow_dmp_fptr)(void);
# define ggo_disable_sigcont 888
# define ggt_disable_sigcont boolean_t
# define ggo_dollar_zcompile 896
# define ggt_dollar_zcompile mstr
# define ggo_dollar_zmode 912
# define ggt_dollar_zmode mval
# define ggo_dollar_zonlnrlbk 944
# define ggt_dollar_zonlnrlbk int
# define ggo_dollar_zroutines 952
# define ggt_dollar_zroutines mstr
# define ggo_error_on_jnl_file_lost 968
# define ggt_error_on_jnl_file_lost unsigned int
# define ggo_fnzsearch_lv_vars 976
# define ggt_fnzsearch_lv_vars lv_val *
# define ggo_fnzsearch_sub_mval 984
# define ggt_fnzsearch_sub_mval mval
# define ggo_fnzsearch_nullsubs_sav 1016
# define ggt_fnzsearch_nullsubs_sav int
# define ggo_gtm_env_init_done 1020
# define ggt_gtm_env_init_done boolean_t
# define ggo_gtm_env_xlate_entry 1024
# define ggt_gtm_env_xlate_entry int
# define gga_gtm_env_xlate_entry ()
typedef int (*ggf_gtm_env_xlate_entry)();
# define ggo_gtm_environment_init 1032
# define ggt_gtm_environment_init boolean_t
# define ggo_gtm_sigusr1_handler 1040
# define ggt_gtm_sigusr1_handler void
# define gga_gtm_sigusr1_handler (void)
typedef void (*ggf_gtm_sigusr1_handler)(void);
# define ggo_gtm_trctbl_cur 1048
# define ggt_gtm_trctbl_cur trctbl_entry *
# define ggo_gtm_trctbl_end 1056
# define ggt_gtm_trctbl_end trctbl_entry *
# define ggo_gtm_trctbl_groups 1064
# define ggt_gtm_trctbl_groups unsigned int
# define ggo_gtm_trctbl_start 1072
# define ggt_gtm_trctbl_start trctbl_entry *
# define ggo_gtm_waitstuck_script 1080
# define ggt_gtm_waitstuck_script mstr
# define ggo_gtmprompt 1096
# define ggt_gtmprompt mstr
# define ggo_in_zwrite 1112
# define ggt_in_zwrite boolean_t
# define ggo_lab_proxy 1120
# define ggt_lab_proxy lab_tabent_proxy
# define ggo_mprof_alloc_reclaim 1136
# define ggt_mprof_alloc_reclaim boolean_t
# define ggo_mprof_chunk_avail_size 1140
# define ggt_mprof_chunk_avail_size int
# define ggo_mprof_env_gbl_name 1144
# define ggt_mprof_env_gbl_name mval
# define ggo_mprof_ptr 1176
# define ggt_mprof_ptr mprof_wrapper *
# define ggo_mprof_reclaim_addr 1184
# define ggt_mprof_reclaim_addr char *
# define ggo_mprof_reclaim_cnt 1192
# define ggt_mprof_reclaim_cnt int
# define ggo_mprof_stack_curr_frame 1200
# define ggt_mprof_stack_curr_frame mprof_stack_frame *
# define ggo_mprof_stack_next_frame 1208
# define ggt_mprof_stack_next_frame mprof_stack_frame *
# define ggo_open_shlib_root 1216
# define ggt_open_shlib_root open_shlib *
# define ggo_parm_pool_ptr 1224
# define ggt_parm_pool_ptr parm_pool *
# define ggo_parms_cnt 1232
# define ggt_parms_cnt unsigned int
# define ggo_pipefifo_interrupt 1236
# define ggt_pipefifo_interrupt int
# define ggo_prof_fp 1240
# define ggt_prof_fp mprof_stack_frame *
# define ggo_trans_code_pop 1248
# define ggt_trans_code_pop mval *
# define ggo_view_ydirt_str 1256
# define ggt_view_ydirt_str char *
# define ggo_view_ydirt_str_len 1264
# define ggt_view_ydirt_str_len int4
# define ggo_zdate_form 1268
# define ggt_zdate_form int4
# define ggo_zintcmd_active 1272
# define ggt_zintcmd_active zintcmd_active_info
# define ggl_zintcmd_active 72
# define ggo_zro_root 1344
# define ggt_zro_root zro_ent *
# define ggo_zsearch_var 1352
# define ggt_zsearch_var lv_val *
# define ggo_zsearch_dir1 1360
# define ggt_zsearch_dir1 lv_val *
# define ggo_zsearch_dir2 1368
# define ggt_zsearch_dir2 lv_val *
# define ggo_fnpca 1376
# define ggt_fnpca fnpc_area
# define ggo_for_stack 19792
# define ggt_for_stack oprtype *
# define ggl_for_stack 256
# define ggo_for_temps 20048
# define ggt_for_temps boolean_t
# define ggl_for_temps 128
# define ggo_last_fnquery_return_sub 20176
# define ggt_last_fnquery_return_sub mval
# define ggl_last_fnquery_return_sub 1024
# define ggo_lcl_coll_xform_buff 21200
# define ggt_lcl_coll_xform_buff char *
# define ggo_parm_ary 21208
# define ggt_parm_ary char *
# define ggl_parm_ary 40
# define ggo_parm_ary_len 21248
# define ggt_parm_ary_len int
# define ggl_parm_ary_len 20
# define ggo_parm_str_len 21268
# define ggt_parm_str_len int
# define ggl_parm_str_len 20
# define ggo_prombuf 21288
# define ggt_prombuf char
# define ggl_prombuf 32
# define ggo_rt_name_tbl 21320
# define ggt_rt_name_tbl hash_table_mname
# define ggo_tp_restart_failhist_arry 21392
# define ggt_tp_restart_failhist_arry char
# define ggl_tp_restart_failhist_arry 32
# define ggo_director_string 21424
# define ggt_director_string char
# define ggl_director_string 32
# define ggo_window_string 21456
# define ggt_window_string char
# define ggl_window_string 32
# define ggo_callin_hashtab 21488
# define ggt_callin_hashtab hash_table_str *
# define ggo_ci_table 21496
# define ggt_ci_table callin_entry_list *
# define ggo_extcall_package_root 21504
# define ggt_extcall_package_root struct extcall_package_list *
# define ggo_gtmci_nested_level 21512
# define ggt_gtmci_nested_level unsigned int
# define ggo_want_empty_gvts 21516
# define ggt_want_empty_gvts boolean_t
# define size_gtm_threadgbl_struct 21520
#else
# define ggo_grabbing_crit 0
# define ggt_grabbing_crit gd_region *
# define ggo_boolchain 8
# define ggt_boolchain triple
# define ggo_boolchain_ptr 144
# define ggt_boolchain_ptr triple *
# define ggo_code_generated 152
# define ggt_code_generated boolean_t
# define ggo_codegen_padlen 156
# define ggt_codegen_padlen int4
# define ggo_compile_time 160
# define ggt_compile_time boolean_t
# define ggo_curtchain 168
# define ggt_curtchain triple *
# define ggo_director_ident 176
# define ggt_director_ident mstr
# define ggo_director_mval 192
# define ggt_director_mval mval
# define ggo_director_token 224
# define ggt_director_token char
# define ggo_dollar_zcstatus 228
# define ggt_dollar_zcstatus int4
# define ggo_expr_depth 232
# define ggt_expr_depth unsigned int
# define ggo_expr_start 240
# define ggt_expr_start triple *
# define ggo_expr_start_orig 248
# define ggt_expr_start_orig triple *
# define ggo_for_nest_level 256
# define ggt_for_nest_level uint4
# define ggo_for_stack_ptr 264
# define ggt_for_stack_ptr oprtype **
# define ggo_gtm_fullbool 272
# define ggt_gtm_fullbool unsigned int
# define ggo_ind_result_array 280
# define ggt_ind_result_array mval **
# define ggo_ind_result_sp 288
# define ggt_ind_result_sp mval **
# define ggo_ind_result_top 296
# define ggt_ind_result_top mval **
# define ggo_ind_source_array 304
# define ggt_ind_source_array mval **
# define ggo_ind_source_sp 312
# define ggt_ind_source_sp mval **
# define ggo_ind_source_top 320
# define ggt_ind_source_top mval **
# define ggo_last_source_column 328
# define ggt_last_source_column short int
# define ggo_pos_in_chain 336
# define ggt_pos_in_chain triple
# define ggo_s2n_intlit 472
# define ggt_s2n_intlit boolean_t
# define ggo_saw_side_effect 476
# define ggt_saw_side_effect boolean_t
# define ggo_shift_side_effects 480
# define ggt_shift_side_effects int
# define ggo_source_error_found 484
# define ggt_source_error_found int4
# define ggo_temp_subs 488
# define ggt_temp_subs boolean_t
# define ggo_trigger_compile 492
# define ggt_trigger_compile boolean_t
# define ggo_window_ident 496
# define ggt_window_ident mstr
# define ggo_window_mval 512
# define ggt_window_mval mval
# define ggo_window_token 544
# define ggt_window_token char
# define ggo_dbinit_max_hrtbt_delta 548
# define ggt_dbinit_max_hrtbt_delta uint4
# define ggo_donot_commit 552
# define ggt_donot_commit boolean_t
# define ggo_donot_write_inctn_in_wcs_recover 556
# define ggt_donot_write_inctn_in_wcs_recover boolean_t
# define ggo_gd_targ_addr 560
# define ggt_gd_targ_addr gd_addr *
# define ggo_gtm_gvundef_fatal 568
# define ggt_gtm_gvundef_fatal boolean_t
# define ggo_gv_extname_size 572
# define ggt_gv_extname_size int4
# define ggo_gv_last_subsc_null 576
# define ggt_gv_last_subsc_null boolean_t
# define ggo_gv_mergekey2 584
# define ggt_gv_mergekey2 gv_key *
# define ggo_gv_reorgkey 592
# define ggt_gv_reorgkey gv_key *
# define ggo_gv_some_subsc_null 600
# define ggt_gv_some_subsc_null boolean_t
# define ggo_gv_sparekey 608
# define ggt_gv_sparekey gv_key *
# define ggo_gv_sparekey_mval 616
# define ggt_gv_sparekey_mval mval
# define ggo_gv_sparekey_size 648
# define ggt_gv_sparekey_size int4
# define ggo_gv_tporigkey_ptr 656
# define ggt_gv_tporigkey_ptr gv_orig_key_array *
# define ggo_in_gvcst_redo_root_search 664
# define ggt_in_gvcst_redo_root_search boolean_t
# define ggo_in_op_gvget 668
# define ggt_in_op_gvget boolean_t
# define ggo_issue_DBROLLEDBACK_anyways 672
# define ggt_issue_DBROLLEDBACK_anyways boolean_t
# define ggo_last_fnquery_return_subcnt 676
# define ggt_last_fnquery_return_subcnt int
# define ggo_last_fnquery_return_varname 680
# define ggt_last_fnquery_return_varname mval
# define ggo_new_dbinit_ipc 712
# define ggt_new_dbinit_ipc int4
# define ggo_ok_to_call_wcs_recover 716
# define ggt_ok_to_call_wcs_recover boolean_t
# define ggo_only_reset_clues_if_onln_rlbk 720
# define ggt_only_reset_clues_if_onln_rlbk boolean_t
# define ggo_prev_gv_target 728
# define ggt_prev_gv_target gv_namehead *
# define ggo_ready2signal_gvundef 736
# define ggt_ready2signal_gvundef boolean_t
# define ggo_semwait2long 740
# define ggt_semwait2long volatile boolean_t
# define ggo_tp_restart_count 744
# define ggt_tp_restart_count uint4
# define ggo_tp_restart_dont_counts 748
# define ggt_tp_restart_dont_counts uint4
# define ggo_tp_restart_entryref 752
# define ggt_tp_restart_entryref mval
# define ggo_tp_restart_failhist_indx 784
# define ggt_tp_restart_failhist_indx int4
# define ggo_tp_restart_needlock_cnt 788
# define ggt_tp_restart_needlock_cnt uint4
# define ggo_tp_restart_needlock_tn 792
# define ggt_tp_restart_needlock_tn trans_num
# define ggo_tprestart_syslog_delta 800
# define ggt_tprestart_syslog_delta int4
# define ggo_tprestart_syslog_limit 804
# define ggt_tprestart_syslog_limit int4
# define ggo_transform 808
# define ggt_transform boolean_t
# define ggo_wcs_recover_done 812
# define ggt_wcs_recover_done boolean_t
# define ggo_in_op_fnnext 816
# define ggt_in_op_fnnext boolean_t
# define ggo_local_collseq 824
# define ggt_local_collseq collseq *
# define ggo_local_collseq_stdnull 832
# define ggt_local_collseq_stdnull boolean_t
# define ggo_lv_null_subs 836
# define ggt_lv_null_subs int
# define ggo_max_lcl_coll_xform_bufsiz 840
# define ggt_max_lcl_coll_xform_bufsiz int
# define ggo_replgbl 848
# define ggt_replgbl replgbl_t
# define ggo_collseq_list 872
# define ggt_collseq_list collseq *
# define ggo_create_fatal_error_zshow_dmp_fptr 880
# define ggt_create_fatal_error_zshow_dmp_fptr void
# define gga_create_fatal_error_zshow_dmp_fptr (void)
typedef void (*ggf_create_fatal_error_zshow_dmp_fptr)(void);
# define ggo_disable_sigcont 888
# define ggt_disable_sigcont boolean_t
# define ggo_dollar_zcompile 896
# define ggt_dollar_zcompile mstr
# define ggo_dollar_zmode 912
# define ggt_dollar_zmode mval
# define ggo_dollar_zonlnrlbk 944
# define ggt_dollar_zonlnrlbk int
# define ggo_dollar_zroutines 952
# define ggt_dollar_zroutines mstr
# define ggo_error_on_jnl_file_lost 968
# define ggt_error_on_jnl_file_lost unsigned int
# define ggo_fnzsearch_lv_vars 976
# define ggt_fnzsearch_lv_vars lv_val *
# define ggo_fnzsearch_sub_mval 984
# define ggt_fnzsearch_sub_mval mval
# define ggo_fnzsearch_nullsubs_sav 1016
# define ggt_fnzsearch_nullsubs_sav int
# define ggo_gtm_env_init_done 1020
# define ggt_gtm_env_init_done boolean_t
# define ggo_gtm_env_xlate_entry 1024
# define ggt_gtm_env_xlate_entry int
# define gga_gtm_env_xlate_entry ()
typedef int (*ggf_gtm_env_xlate_entry)();
# define ggo_gtm_environment_init 1032
# define ggt_gtm_environment_init boolean_t
# define ggo_gtm_sigusr1_handler 1040
# define ggt_gtm_sigusr1_handler void
# define gga_gtm_sigusr1_handler (void)
typedef void (*ggf_gtm_sigusr1_handler)(void);
# define ggo_gtm_trctbl_cur 1048
# define ggt_gtm_trctbl_cur trctbl_entry *
# define ggo_gtm_trctbl_end 1056
# define ggt_gtm_trctbl_end trctbl_entry *
# define ggo_gtm_trctbl_groups 1064
# define ggt_gtm_trctbl_groups unsigned int
# define ggo_gtm_trctbl_start 1072
# define ggt_gtm_trctbl_start trctbl_entry *
# define ggo_gtm_waitstuck_script 1080
# define ggt_gtm_waitstuck_script mstr
# define ggo_gtmprompt 1096
# define ggt_gtmprompt mstr
# define ggo_in_zwrite 1112
# define ggt_in_zwrite boolean_t
# define ggo_lab_proxy 1120
# define ggt_lab_proxy lab_tabent_proxy
# define ggo_mprof_alloc_reclaim 1136
# define ggt_mprof_alloc_reclaim boolean_t
# define ggo_mprof_chunk_avail_size 1140
# define ggt_mprof_chunk_avail_size int
# define ggo_mprof_env_gbl_name 1144
# define ggt_mprof_env_gbl_name mval
# define ggo_mprof_ptr 1176
# define ggt_mprof_ptr mprof_wrapper *
# define ggo_mprof_reclaim_addr 1184
# define ggt_mprof_reclaim_addr char *
# define ggo_mprof_reclaim_cnt 1192
# define ggt_mprof_reclaim_cnt int
# define ggo_mprof_stack_curr_frame 1200
# define ggt_mprof_stack_curr_frame mprof_stack_frame *
# define ggo_mprof_stack_next_frame 1208
# define ggt_mprof_stack_next_frame mprof_stack_frame *
# define ggo_open_shlib_root 1216
# define ggt_open_shlib_root open_shlib *
# define ggo_parm_pool_ptr 1224
# define ggt_parm_pool_ptr parm_pool *
# define ggo_parms_cnt 1232
# define ggt_parms_cnt unsigned int
# define ggo_pipefifo_interrupt 1236
# define ggt_pipefifo_interrupt int
# define ggo_prof_fp 1240
# define ggt_prof_fp mprof_stack_frame *
# define ggo_trans_code_pop 1248
# define ggt_trans_code_pop mval *
# define ggo_view_ydirt_str 1256
# define ggt_view_ydirt_str char *
# define ggo_view_ydirt_str_len 1264
# define ggt_view_ydirt_str_len int4
# define ggo_zdate_form 1268
# define ggt_zdate_form int4
# define ggo_zintcmd_active 1272
# define ggt_zintcmd_active zintcmd_active_info
# define ggl_zintcmd_active 72
# define ggo_zro_root 1344
# define ggt_zro_root zro_ent *
# define ggo_zsearch_var 1352
# define ggt_zsearch_var lv_val *
# define ggo_zsearch_dir1 1360
# define ggt_zsearch_dir1 lv_val *
# define ggo_zsearch_dir2 1368
# define ggt_zsearch_dir2 lv_val *
# define ggo_fnpca 1376
# define ggt_fnpca fnpc_area
# define ggo_for_stack 19792
# define ggt_for_stack oprtype *
# define ggl_for_stack 256
# define ggo_for_temps 20048
# define ggt_for_temps boolean_t
# define ggl_for_temps 128
# define ggo_last_fnquery_return_sub 20176
# define ggt_last_fnquery_return_sub mval
# define ggl_last_fnquery_return_sub 1024
# define ggo_lcl_coll_xform_buff 21200
# define ggt_lcl_coll_xform_buff char *
# define ggo_parm_ary 21208
# define ggt_parm_ary char *
# define ggl_parm_ary 40
# define ggo_parm_ary_len 21248
# define ggt_parm_ary_len int
# define ggl_parm_ary_len 20
# define ggo_parm_str_len 21268
# define ggt_parm_str_len int
# define ggl_parm_str_len 20
# define ggo_prombuf 21288
# define ggt_prombuf char
# define ggl_prombuf 32
# define ggo_rt_name_tbl 21320
# define ggt_rt_name_tbl hash_table_mname
# define ggo_tp_restart_failhist_arry 21392
# define ggt_tp_restart_failhist_arry char
# define ggl_tp_restart_failhist_arry 32
# define ggo_director_string 21424
# define ggt_director_string char
# define ggl_director_string 32
# define ggo_window_string 21456
# define ggt_window_string char
# define ggl_window_string 32
# define ggo_callin_hashtab 21488
# define ggt_callin_hashtab hash_table_str *
# define ggo_ci_table 21496
# define ggt_ci_table callin_entry_list *
# define ggo_extcall_package_root 21504
# define ggt_extcall_package_root struct extcall_package_list *
# define ggo_gtmci_nested_level 21512
# define ggt_gtmci_nested_level unsigned int
# define ggo_want_empty_gvts 21516
# define ggt_want_empty_gvts boolean_t
# define size_gtm_threadgbl_struct 21520
#endif
#endif