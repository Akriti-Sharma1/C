#include "lab4.h"

Player* create_player(char name[], char id[]){
	/**
		Creates and returns a pointer to a newly
		created dynamically allocated Person struct,
		with its <name> and <id> fields initialized
		to the values given by the respectively named 
		parameters.
		
		Hint: strcpy(...) from <string.h> may be helpful.
	*/
  struct Player* player = (struct Player*) malloc(sizeof(struct Player));
  strcpy(player->name,name);
  strcpy(player->id,id);

  return player;
  
}
/*int main(){
  
  Player* p1 = create_player("Noob_player", "N01");
	Player* p2 = create_player("Beginner0101", "B06");
  printf("Player 1: %s, %s\n", p1->name, p1->id);
  printf("Player 2: %s, %s", p2->name, p2->id);
  
}*/

PlayerRecord* create_leaf_record(Player* p){
	/**
		Creates and returns a pointer to a newly created
		dynamically allocated PlayerRecord struct. 
		
		The record created is for the starting bracket
		of a tournament, for player <p>, where <p> is
		a dynamically allocated Player struct as returned
		by create_player(...).
		
		Initializes the new PlayerRecord to have 0 wins 
		and 0 losses; the left_child, right_child, and 
		parent are set to NULL.
		
		The player field should be set to <p>.
	*/
  struct PlayerRecord* record = (struct PlayerRecord*) malloc(sizeof(struct PlayerRecord));
  record->player = p;
  record->game_records[WINS] = 0;
  record->game_records[LOSSES] = 0;
  record->parent = NULL;
  record->left_child = NULL;
  record->right_child = NULL;

  return record;

}
/*int main(){
  
  Player* p1 = create_player("Noob_player", "N01");
	Player* p2 = create_player("Beginner0101", "B06");

  //PlayerRecord* round1_outcome1 = add_match(
		//create_leaf_record(p1), create_leaf_record(p2), 
		//10, 13
	//);
  //printf("%s, %s", p1->name, p1->id);
  //PlayerRecord* record = create_leaf_record(p1);
  printf("%s, %s", record->player->name, record->player->id);
  //printf("%s", round1_outcome1->player->name);
  
  
}*/

PlayerRecord* add_match(
	PlayerRecord* p1, PlayerRecord* p2, 
	int p1_wins, int p2_wins
){
	
	//Creates and returns a pointer to a newly created dynamically allocated PlayerRecord struct.
  struct PlayerRecord* new_record = (struct PlayerRecord*) malloc(sizeof(struct PlayerRecord));
	
	//Joins the tournament trees given by <p1> and <p2>, where <p1> and <p2> are dynamically allocated PlayerRecord structs as returned by create_leaf_record(...).

	//Updates <p1->parent> and <p2->parent> to be the newly created PlayerRecord. 
  p1->parent = new_record;
  p2->parent = new_record;

//Updates the left_child and right_child of the newly created PlayerRecord to reflect the loser and winner of the match, respectively.
  int total_games = p1_wins + p2_wins;
  int p1_losses = total_games - p1_wins;
  int p2_losses = total_games - p2_wins;
  if(p1_wins > p2_wins){
    if(p1->left_child == NULL){
      new_record->left_child = p2;
      new_record->right_child = p1;
      }
    else{
      new_record->right_child = p1->right_child;
      new_record->left_child = p2->right_child;
    }
    new_record->game_records[WINS] = p1_wins;
    new_record->game_records[LOSSES] = p2_wins;
    return new_record;
  }else{
    if(p1->left_child == NULL){
      new_record->left_child = p1;
      new_record->right_child = p2;
    } else{
      new_record->right_child = p2->right_child;
      new_record->left_child = p1->right_child;
    }
    new_record->game_records[WINS] = p2_wins;
    new_record->game_records[LOSSES] = p1_wins;
    return new_record;
  }
  //return new_record;

//Fills the new PlayerRecord's game_records field.
  
	
//<p1->parent> and <p2->parent> are guaranteed to be NULL.
	

}
/*int main(){
  
  Player* p1 = create_player("Noob_player", "N01");
	Player* p2 = create_player("Beginner0101", "B06");
  // IMPLIES PLAYER 2 WINS
  PlayerRecord* round1_outcome1 = add_match(
		create_leaf_record(p1), create_leaf_record(p2), 
		10, 13
	);
  //printf("wins: %d, Losses: %d\n", round1_outcome1->game_records[WINS], round1_outcome1->game_records[LOSSES]);
  //printf("LOSER: %s, %s\n", round1_outcome1->left_child->player->name, round1_outcome1->left_child->player->id);
  //printf("WINNER: %s, %s\n", round1_outcome1->right_child->player->name, round1_outcome1->right_child->player->id);
  
  
  //printf("wins: %s, Losses: %d", round1_outcome1->player->name, round1_outcome1->game_records[LOSSES]);  
  
  
  
}*/

int get_player_rank(char player_id[], PlayerRecord* root){
	/**
	Get the rank of the player identified by <player_id>.
	<root> refers to the root of a completed tournament.
	
	You may assume that each player has a unique id.
	*/
	/**
	*root == NULL iff the tree is empty.
	**/
  //PlayerRecord* curr_node  = root;
  if(root == NULL){
    return 0;
  }
  if (strcmp(root->right_child->player->id, player_id) == 0){
    return 1;
  }
  
  int find_on_right = get_player_rank(player_id, root->right_child);
  // we find the target node in the right subtree
  /*if(find_on_right !=0){
    return find_on_right + 1;
  }

  //... similarly for the left subtree
  int find_on_left = get_player_rank(player_id, root->left_child);
  // we find the target node in the right subtree
  if(find_on_left !=0){
    return find_on_right + 1;
  }*/
 
  return 0; // the target node is not under the subtree whose head is curr_node.
	/*if (root == NULL){
		return 0;
    // use strcmp
	} else if (root->player->id == player_id){
		return 1;
	} else if (player_id > root->player->id) {
		return get_player_rank(player_id, root->right_child );
	} else {
		get_player_rank(player_id, root->left_child);
	}*/

}
int main(){
  	Player* p1 = create_player("Noob_player", "N01");
	Player* p2 = create_player("Beginner0101", "B06");
	
	Player* p3 = create_player("FunnyGuy", "F22");
	Player* p4 = create_player("LaserBeam", "L46");
	
	Player* p5 = create_player("LlamaDog", "L28");
	Player* p6 = create_player("CatPotato", "C26");

	Player* p7 = create_player("PotatoChip", "P16");
	Player* p8 = create_player("Loser1111", "L00");
	
	//Prelims - 4 matches
	PlayerRecord* round1_outcome1 = add_match(
		create_leaf_record(p1), create_leaf_record(p2), 
		10, 13
	);
	PlayerRecord* round1_outcome2 = add_match(
		create_leaf_record(p3), create_leaf_record(p4), 
		5, 13
	);
	PlayerRecord* round1_outcome3 = add_match(
		create_leaf_record(p5), create_leaf_record(p6), 
		2, 13
	);
	PlayerRecord* round1_outcome4 = add_match(
		create_leaf_record(p7), create_leaf_record(p8), 
		13, 0
	);
	
	// Semifinals - 2 matches
	PlayerRecord* round2_outcome1 = add_match(
		round1_outcome1, round1_outcome2, 
		13, 7
	);
	PlayerRecord* round2_outcome2 = add_match(
		round1_outcome3, round1_outcome4, 
		10, 13
	);
	
	// Finals - 1 match
	PlayerRecord* round3_outcome = add_match(
		round2_outcome1, round2_outcome2, 
		8, 13
	);
//printf("%s ", round3_outcome->player->id);  
  get_player_rank("N01", round3_outcome);
}

/**

	========== PROVIDED FUNCTIONS BELOW ==========
	DO NOT MODIFY.
*/

void clear_tournament_records_helper(
	PlayerRecord* curr, PlayerRecord*** records, 
	int* num_records, int* max_records
){
	/**
		Performs a pre-order traversal to retrieve all
		the player records and stores them in <records>,
		an array of pointer to PlayerRecord.
		
		Updates the dynamic array when needed by doubling the 
		size. If the dynamic array is resized, <*max_records> 
		is updated.
		
		<*num_records> is updated to reflect the total number 
		of records.
	
		
	if ((*max_records) == (*num_records)){
		// resize
		(*records) = realloc(*records, sizeof(PlayerRecord*) * (*max_records) * 2);
		(*max_records) *= 2;
	} 
	
	(*records)[*num_records] = curr;
	(*num_records)++;

	if (curr->left_child != NULL){
		clear_tournament_records_helper(
			curr->left_child, records, 
			num_records, max_records
		);
	}
	
	if (curr->right_child != NULL){
		clear_tournament_records_helper(
			curr->right_child, records, 
			num_records, max_records
		);
	}*/
}

void clear_tournament_records(PlayerRecord** root){
	/**
		Frees all memory associated with the tournament,
		EXCLUDING the Player(s)
	
	int num_records = 0;
	int max_records = 10;
	
	PlayerRecord** records = (PlayerRecord**)malloc(sizeof(PlayerRecord*) * max_records);
	if ((*root) != NULL){
		clear_tournament_records_helper(*root, &records, &num_records, &max_records);
	}
	
	for (int i=0; i<num_records; i++){
		free(records[i]);
	}
	*root = NULL;
	free(records);*/
}

void print_tournament_records(PlayerRecord* curr, PlayerRecord* root){
	/**
		Prints out the tournament records as a post-order traversal.
	
	if(curr->left_child != NULL){
		print_tournament_records(curr->left_child, root); 
		print_tournament_records(curr->right_child, root);
		
		fprintf(stdout, "%s VS %s\nRESULT: ", curr->left_child->player->id, curr->right_child->player->id);
	}
	
	fprintf(stdout, "%s with Wins: %d Losses: %d\n", 
		curr->player->id, 
		curr->game_records[WINS],
		curr->game_records[LOSSES]
	);*/
	
}

int player_in_list(Player* p, Player** player_list, int count_el){
	/**
		Returns 1 if <p> is found in <player_list>, returns 0 
		otherwise.
	*/
	for (int i=0; i<count_el; i++){
		if (p->id == (player_list[i])->id) {
			return 1;
		} 
	} return 0;
}

void collect_at_rank(
	PlayerRecord* curr,
	PlayerRecord* root, 
	Player** players_at_curr_rank, 
	int rank,
	int* count_el, 
	int* max_el
){	
	/**
		Collects all players with rank <rank> and stores them in <players_at_curr_rank>,
		updating <*count_el> and <*max_el> as needed.
	*/
	int tmp_rank = get_player_rank(curr->player->id, root);
	if (tmp_rank == rank && !player_in_list(curr->player, players_at_curr_rank, *count_el)){
		if ((*count_el) == (*max_el)){
			// resize
			players_at_curr_rank = realloc(players_at_curr_rank, sizeof(Player*) * (*max_el) * 2);
			(*max_el) *= 2;
		}
		players_at_curr_rank[*count_el] = curr->player;
		(*count_el)++;
	}
	if (curr->left_child != NULL){
		collect_at_rank(curr->left_child, root, players_at_curr_rank, rank, count_el, max_el);
	}
	if (curr->right_child != NULL){
		collect_at_rank(curr->right_child, root, players_at_curr_rank, rank, count_el, max_el);
	}
}

void print_with_rank(PlayerRecord* root){
	/**
	Prints a record of all players and their rank once the tournament
	has concluded. <root> refers to a completed tournament tree.
	
	Warning: very inefficient, do not use on large trees
	
	int count_el = 0;
	int max_el = 10;
	int curr_rank = 1;
	Player** players_at_curr_rank = (Player**)malloc(sizeof(Player*) * max_el);
	
	do {
		count_el = 0;
		collect_at_rank(root, root, players_at_curr_rank, curr_rank, &count_el, &max_el); 
		for (int i=0; i<count_el; i++){
			fprintf(stdout, "Rank %d: %s\n", curr_rank, (players_at_curr_rank[i])->id);
		}
		curr_rank++;
	} while (count_el != 0);
	
	free(players_at_curr_rank);*/
}

/*int main(){
  Player* p1 = create_player("Noob_player", "N01");
	Player* p2 = create_player("Beginner0101", "B06");
	
	Player* p3 = create_player("FunnyGuy", "F22");
	Player* p4 = create_player("LaserBeam", "L46");
	
	Player* p5 = create_player("LlamaDog", "L28");
	Player* p6 = create_player("CatPotato", "C26");

	Player* p7 = create_player("PotatoChip", "P16");
	Player* p8 = create_player("Loser1111", "L00");
	
	//Prelims - 4 matches
	PlayerRecord* round1_outcome1 = add_match(
		create_leaf_record(p1), create_leaf_record(p2), 
		10, 13
	);
	PlayerRecord* round1_outcome2 = add_match(
		create_leaf_record(p3), create_leaf_record(p4), 
		5, 13
	);
	PlayerRecord* round1_outcome3 = add_match(
		create_leaf_record(p5), create_leaf_record(p6), 
		2, 13
	);
	PlayerRecord* round1_outcome4 = add_match(
		create_leaf_record(p7), create_leaf_record(p8), 
		13, 0
	);
	
	// Semifinals - 2 matches
	PlayerRecord* round2_outcome1 = add_match(
		round1_outcome1, round1_outcome2, 
		13, 7
	);
	PlayerRecord* round2_outcome2 = add_match(
		round1_outcome3, round1_outcome4, 
		10, 13
	);
  /*printf("wins: %d, Losses: %d\n", round2_outcome1->game_records[WINS], round2_outcome2->game_records[LOSSES]);
  printf("LOSER: %s, \n", round2_outcome2->left_child->player->name);
    //round3_outcome->left_child->player->id);
  printf("WINNER: %s, %s\n", round2_outcome2->right_child->player->name, round2_outcome2->right_child->player->id);
	
	// Finals - 1 match
	PlayerRecord* round3_outcome = add_match(
		round2_outcome1, round2_outcome2, 
		8, 13
	);
  printf("wins: %d, Losses: %d\n", round3_outcome->game_records[WINS], round3_outcome->game_records[LOSSES]);
  printf("LOSER: %s, %s\n", round3_outcome->left_child->player->name, round3_outcome->left_child->player->id);
   printf("WINNER: %s, %s\n", round3_outcome->right_child->player->name, round3_outcome->right_child->player->id);
	/*printf("%s\n", round3_outcome->left_child->player->id);
  printf("%s\n", round3_outcome->right_child->player->id);
  printf("AND THE WINNER IS...\n");
  printf("%s, %s!!!!", 
    round3_outcome->right_child->player->name, 
    round3_outcome->right_child->player->id);
}*/


