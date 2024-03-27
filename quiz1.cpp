#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song
{
    char title[100];
    char artist[100];
    char duration[10];
    Song *next;
    Song *prev;
};

Song *head = NULL;
Song *tail = NULL;

Song *createSong(const char *title, const char *artist, const char *duration){
    Song *newSong = (Song*)malloc(sizeof(Song));

    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->duration, duration);
    newSong->next = NULL;
    newSong->prev = NULL;

    return newSong;
}

void insertSong(const char *title, const char *artist, const char *duration){
    Song *newSong = createSong(title, artist, duration);
    if(!head){
        head = tail = newSong;
    }
    else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
}

void showPlaylist(){
    if(!head){
        printf("Playlist is empty!.\n");
    }
    else {
        Song *temp = head;
        printf("Playlist:\n");
        while(temp){
            printf("Title: %s | Artist: %s | Duration: %s\n", temp->title, temp->artist, temp->duration);
            temp = temp->next;
        }
    }
}

void insertAfter(const char *target, const char *title, const char *artist, const char *duration){
    Song *newSong = createSong(title, artist, duration);

    if(!head){
        printf("Target not found!\n"); // (1.)
        // head = tail = NULL; (2.)
    }
    else {
        Song *temp = head;
        while (temp){
            if(strcmp(target, temp->title) == 0){
                // temp == tail
                if(temp == tail){
                    tail->next = newSong;
                    newSong->prev = tail;
                    tail = newSong;
                }
                else {
                    Song *left = temp;
                    Song *right = temp->next;
                    left->next = newSong;
                    newSong->prev = left;
                    newSong->next = right;
                    right->prev = newSong;
                }
                printf("Song '%s' inserted after '%s'.\n", newSong->title, temp->title);
                return;
            }
            temp = temp->next;
        }
        printf("Target song not found!\n");
    }
}

void insertBefore(const char *target, const char *title, const char *artist, const char *duration){
    Song *newSong = createSong(title, artist, duration);

    if(!head){
        printf("Target song not found!\n");
    }
    else {
        if(strcmp(head->title, target) == 0){
            newSong->next = head;
            head->prev = newSong;
            head = newSong;
            return;
        }
        else {
            Song *temp = head;
            while (temp){
                if(strcmp(temp->title, target) == 0){
                    Song *left = temp->prev;
                    Song *right = temp;
                    left->next = newSong;
                    newSong->prev = left;
                    newSong->next = right;
                    right->prev = newSong;
                    printf("Song '%s' inserted before '%s'.\n", newSong->title, temp->title);
                    return;
                }
                temp = temp->next;
            }
            printf("Target song not found!\n");
        }
    }
}

void popHead(){
    if(!head){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
    }
    else {
        head = head->next;
        free(head->prev);
        head->prev = NULL;
    }
}

void popTail(){
    if(!head){
        return;
    }
    else if(head == tail){
        free(head);
        head = tail = NULL;
    }
    else {
        tail = tail->prev;
        free(tail->next);
        tail->next = NULL;
    }
}

void removeSong(const char *target){
    if(!head){
        printf("Playlist is empty.\n");
    }
    else if(strcmp(head->title, target) == 0){
        printf("Song '%s' removed from playlist.\n", head->title);
        popHead();
    }
    else if(strcmp(tail->title, target) == 0){
        printf("Song '%s' removed from playlist.\n", tail->title);
        popTail();
    }
    else {
        Song *temp = head;
        while(temp){
            if(strcmp(temp->title, target) == 0){
                printf("Song '%s' removed from playlist.\n", temp->title);
                Song *left = temp->prev;
                Song *right = temp->next;
                left->next = right;
                right->prev = left;
                free(temp);
                return;
            }
            temp = temp->next;
        }
        printf("Target song not found!\n");
    }
}

void clearPlaylist(){
    while(head){
        popHead();
    }
}

int main(){

    insertSong("Song Title 1", "Artist 1", "03.30");
    insertSong("Song Title 2", "Artist 2", "04.15");
    insertSong("Song Title 3", "Artist 3", "02.50");
    insertSong("Song Title 4", "Artist 4", "05.00");

    showPlaylist();

    insertAfter("Song Title 2", "Song Title 2.5", "Artist 2.5", "01.45");
    insertBefore("Song Title 4", "Song Title 3.5", "Artist 3.5", "02.30");

    showPlaylist();

    removeSong("Song Title 2.5");
    removeSong("Song Title 4");

    clearPlaylist();

    showPlaylist();

    return 0;
}