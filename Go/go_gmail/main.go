package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"

	"golang.org/x/oauth2"
	"golang.org/x/oauth2/google"
	"google.golang.org/api/gmail/v1"
)

func main() {
    // Load credentials from JSON file
    credentialsFile := "credentials.json"
    creds, err := readCredentials(credentialsFile)
    if err != nil {
        log.Fatalf("Unable to read credentials: %v", err)
    }

    // Initialize the Gmail API client
    ctx := context.Background()
    config, err := google.ConfigFromJSON(creds, gmail.GmailReadonlyScope)
    if err != nil {
        log.Fatalf("Unable to initialize Gmail client: %v", err)
    }
    client := getClient(ctx, config)

    // Fetch emails with label "inbox"
    label := "INBOX"
    user := "me"
    messages, err := client.Users.Messages.List(user).LabelIds(label).Do()
    if err != nil {
        log.Fatalf("Unable to retrieve messages: %v", err)
    }

    // Print the IDs of the fetched messages
    fmt.Println("Messages in Inbox:")
    if len(messages.Messages) == 0 {
        fmt.Println("No messages found.")
    } else {
        for _, message := range messages.Messages {
            fmt.Println(" - ", message.Id)
        }
    }
}

// Read credentials from JSON file
func readCredentials(filepath string) ([]byte, error) {
    file, err := os.Open(filepath)
    if err != nil {
        return nil, err
    }
    defer file.Close()
    fileInfo, err := file.Stat()
    if err != nil {
        return nil, err
    }
    size := fileInfo.Size()
    buffer := make([]byte, size)
    _, err = file.Read(buffer)
    if err != nil {
        return nil, err
    }
    return buffer, nil
}

// Create a new Gmail API client
func getClient(ctx context.Context, config *oauth2.Config) *gmail.Service {
    tokenFile := "token.json"
    token, err := tokenFromFile(tokenFile)
    if err != nil {
        // If token file doesn't exist, initiate OAuth2 flow
        token = getTokenFromWeb(config)
        saveToken(tokenFile, token)
    }
    client := config.Client(ctx, token)
    srv, err := gmail.New(client)
    if err != nil {
        log.Fatalf("Unable to create Gmail client: %v", err)
    }
    return srv
}

// Retrieves a token from a local file.
func tokenFromFile(file string) (*oauth2.Token, error) {
    f, err := os.Open(file)
    if err != nil {
        return nil, err
   }
    defer f.Close()
    tok := &oauth2.Token{}
    err = json.NewDecoder(f).Decode(tok)
    return tok, err
}

// Request a token from the web, then returns the retrieved token.
func getTokenFromWeb(config *oauth2.Config) *oauth2.Token {
    authURL := config.AuthCodeURL("state-token", oauth2.AccessTypeOffline)
    fmt.Printf("Go to the following link in your browser then type the "+
        "authorization code: \n%v\n", authURL)

    // Start a local HTTP server to handle OAuth2 callback
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        code := r.FormValue("code")
        tok, err := config.Exchange(context.Background(), code)
        if err != nil {
            log.Fatalf("Unable to retrieve token from web: %v", err)
        }
        w.Write([]byte("Authorization successful. You can close this window."))
        saveToken("token.json", tok)
    })
    go http.ListenAndServe(":8080", nil)

    // Wait for authorization code from user
    var code string
    if _, err := fmt.Scan(&code); err != nil {
        log.Fatalf("Unable to read authorization code: %v", err)
    }

    return nil // Return nil since the token is saved via the HTTP handler
}

// Saves a token to a file path.
func saveToken(file string, token *oauth2.Token) {
    fmt.Printf("Saving credential file to: %s\n", file)
    f, err := os.Create(file)
    if err != nil {
        log.Fatalf("Unable to save token: %v", err)
    }
    defer f.Close()
    json.NewEncoder(f).Encode(token)
}
